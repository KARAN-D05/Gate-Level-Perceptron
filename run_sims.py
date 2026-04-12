#!/usr/bin/env python3
"""
run_sims.py -- Cross-platform Verilog Simulation Runner
Automatically discovers all Verilog-Implementation folders, pairs DUT + testbench,
and provides an interactive simulation menu.

Supports: Linux (apt) | Windows (winget/choco)
Extensible: drop any new folder with Verilog-Implementation/ inside -- zero changes needed.
"""

import os
import sys
import subprocess
import platform
import shutil
import tempfile
from pathlib import Path
from dataclasses import dataclass
from typing import Optional
from itertools import groupby

# ---------------------------------------------
# CONFIG -- change these if your naming differs
# ---------------------------------------------
IMPL_FOLDER_NAME = "Verilog-Implementation"   # subfolder name to search for
TB_SUFFIX        = "_tb.v"                     # testbench suffix
SRC_SUFFIX       = ".v"                        # source extension


# ---------------------------------------------
# ANSI COLOURS (disabled automatically on Windows if no ANSI support)
# ---------------------------------------------
def _supports_color() -> bool:
    if platform.system() == "Windows":
        try:
            import ctypes
            kernel32 = ctypes.windll.kernel32
            kernel32.SetConsoleMode(kernel32.GetStdHandle(-11), 7)
            return True
        except Exception:
            return False
    return sys.stdout.isatty()

USE_COLOR = _supports_color()

def c(text: str, code: str) -> str:
    return f"\033[{code}m{text}\033[0m" if USE_COLOR else text

def bold(t):   return c(t, "1")
def green(t):  return c(t, "32")
def yellow(t): return c(t, "33")
def cyan(t):   return c(t, "36")
def red(t):    return c(t, "31")
def dim(t):    return c(t, "2")


# ---------------------------------------------
# DATA
# ---------------------------------------------
@dataclass
class SimPair:
    project  : str
    dut_path : Path
    tb_path  : Path
    dut_name : str

    def label(self) -> str:
        return f"{self.project}  /  {self.dut_name}"


# ---------------------------------------------
# DISCOVERY
# ---------------------------------------------
def discover_pairs(root: Path) -> list[SimPair]:
    pairs: list[SimPair] = []

    for impl_dir in sorted(root.rglob(IMPL_FOLDER_NAME)):
        if not impl_dir.is_dir():
            continue

        project_name = impl_dir.parent.name

        src_files = [
            f for f in impl_dir.glob(f"*{SRC_SUFFIX}")
            if not f.name.endswith(TB_SUFFIX)
        ]

        for src in sorted(src_files):
            dut_name = src.stem
            tb_path  = impl_dir / f"{dut_name}{TB_SUFFIX}"

            if tb_path.exists():
                pairs.append(SimPair(
                    project  = project_name,
                    dut_path = src,
                    tb_path  = tb_path,
                    dut_name = dut_name,
                ))
            else:
                print(yellow(f"  [warn] No testbench found for {src.relative_to(root)} -- skipping"))

    return pairs


# ---------------------------------------------
# ENVIRONMENT SETUP
# ---------------------------------------------
def _run(cmd: list[str], check=True) -> subprocess.CompletedProcess:
    return subprocess.run(cmd, check=check)


def _tool_installed(name: str) -> bool:
    return shutil.which(name) is not None


def setup_linux(missing: list[str]) -> bool:
    print(cyan(f"\n  Installing: {', '.join(missing)} via apt ..."))
    try:
        _run(["sudo", "apt-get", "update", "-qq"])
        _run(["sudo", "apt-get", "install", "-y"] + missing)
        return True
    except subprocess.CalledProcessError:
        print(red("  apt install failed. Please install manually and re-run."))
        return False


def setup_windows(missing: list[str]) -> bool:
    pkg_map = {
        "iverilog": "IcarusVerilog.IcarusVerilog",
        "gtkwave" : "gtkwave.gtkwave",
    }

    if _tool_installed("winget"):
        print(cyan(f"\n  Installing via winget: {', '.join(missing)} ..."))
        ok = True
        for tool in missing:
            pkg = pkg_map.get(tool, tool)
            res = _run(["winget", "install", "--id", pkg, "-e", "--silent"], check=False)
            if res.returncode != 0:
                ok = False
                print(yellow(f"  winget failed for {tool}, trying choco ..."))
                if _tool_installed("choco"):
                    res2 = _run(["choco", "install", tool, "-y"], check=False)
                    if res2.returncode != 0:
                        print(red(f"  choco also failed for {tool}."))
                        ok = False
        if not ok:
            print(red("\n  Some tools could not be installed automatically."))
            print(red("  Please install manually:"))
            print(red("    iverilog: https://bleyer.org/icarus/"))
            print(red("    gtkwave:  https://gtkwave.sourceforge.net/"))
        return ok

    print(red("  winget not found. Please install iverilog and gtkwave manually:"))
    print(red("    iverilog: https://bleyer.org/icarus/"))
    print(red("    gtkwave:  https://gtkwave.sourceforge.net/"))
    return False


def ensure_tools() -> bool:
    tools   = ["iverilog", "gtkwave"]
    missing = [t for t in tools if not _tool_installed(t)]

    if not missing:
        print(green("  + iverilog and gtkwave are installed."))
        return True

    print(yellow(f"\n  Missing tools: {', '.join(missing)}"))
    answer = input("  Install them now? [Y/n]: ").strip().lower()
    if answer in ("", "y", "yes"):
        os_name = platform.system()
        if os_name == "Linux":
            apt_map = {"iverilog": "iverilog", "gtkwave": "gtkwave"}
            return setup_linux([apt_map[t] for t in missing])
        elif os_name == "Windows":
            return setup_windows(missing)
        elif os_name == "Darwin":
            if _tool_installed("brew"):
                print(cyan(f"\n  Installing via brew: {', '.join(missing)} ..."))
                subprocess.run(["brew", "install"] + missing, check=False)
                return all(_tool_installed(t) for t in missing)
            else:
                print(red("  brew not found. Install Homebrew first: https://brew.sh"))
                return False
    else:
        print(red("  Skipping install. Simulations may fail."))
        return False


# ---------------------------------------------
# SIMULATION
# ---------------------------------------------
def run_simulation(pair: SimPair, open_wave: bool = True) -> bool:
    with tempfile.TemporaryDirectory() as tmpdir:
        out_bin    = Path(tmpdir) / "sim.out"
        source_dir = pair.tb_path.parent        # vvp runs here so VCD lands next to .v files

        # ── Compile ──────────────────────────────
        print(cyan(f"\n  Compiling {pair.dut_name} ..."))
        compile_res = subprocess.run(
            ["iverilog", "-o", str(out_bin), str(pair.dut_path), str(pair.tb_path)],
            capture_output=True,
            text=True,
        )

        if compile_res.returncode != 0:
            print(red("  x Compilation failed:\n"))
            print(compile_res.stderr)
            return False
        print(green("  + Compilation successful"))

        # ── Simulate ─────────────────────────────
        print(cyan("  Running simulation ...\n"))

        # Run from source_dir so $dumpfile("x.vcd") writes next to the .v files
        sim_res = subprocess.run(
            ["vvp", str(out_bin)],
            cwd=str(source_dir),
            capture_output=True,
            text=True,
        )

        # Print all $display / $monitor output
        if sim_res.stdout:
            print(sim_res.stdout)
        if sim_res.stderr:
            print(sim_res.stderr)

        if sim_res.returncode != 0:
            print(red("  x Simulation exited with errors."))
            return False

        # ── Waveform ─────────────────────────────
        # Look in source folder (where vvp ran) and tempdir
        search_dirs = [source_dir, Path(tmpdir)]
        vcd_files   = [f for d in search_dirs for f in Path(d).glob("*.vcd")]

        if vcd_files and open_wave:
            vcd = vcd_files[0]
            print(cyan(f"\n  Opening waveform: {vcd.name}"))
            subprocess.Popen(
                ["gtkwave", str(vcd)],
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
            )
        elif not vcd_files:
            print(dim("  (No .vcd produced -- add $dumpfile/$dumpvars to testbench for waveforms)"))

        return True


# ---------------------------------------------
# MENU
# ---------------------------------------------
def print_banner():
    print()
    print(bold(cyan("+--------------------------------------------------+")))
    print(bold(cyan("|         Verilog Simulation Runner                |")))
    print(bold(cyan("+--------------------------------------------------+")))
    print()


def print_menu(pairs: list[SimPair]):
    print()
    last_project = None
    for i, p in enumerate(pairs, start=1):
        if p.project != last_project:
            print(f"  {bold(yellow(p.project))}")
            last_project = p.project
        print(f"    {bold(str(i)):>4}.  {p.dut_name}")
    print()
    print(f"  {bold('a')}  -- run ALL simulations")
    print(f"  {bold('r')}  -- re-scan for new files")
    print(f"  {bold('q')} / {bold('exit')}  -- quit")
    print()


def interactive_loop(pairs: list[SimPair], root: Path):
    while True:
        print_menu(pairs)
        raw = input(bold("  Select > ")).strip().lower()

        if raw in ("q", "quit", "exit", ""):
            print(green("\n  Goodbye.\n"))
            break

        elif raw == "r":
            pairs = discover_pairs(root)
            if not pairs:
                print(yellow("  No simulation pairs found."))
            else:
                print(green(f"  Re-scanned: {len(pairs)} pair(s) found."))
            continue

        elif raw == "a":
            print(bold(cyan(f"\n  Running all {len(pairs)} simulation(s) ...")))
            results = []
            for p in pairs:
                print(bold(f"\n  -- {p.label()} --"))
                ok = run_simulation(p, open_wave=False)
                results.append((p.label(), ok))
            print()
            print(bold("  -- Results --"))
            for label, ok in results:
                status = green("PASS") if ok else red("FAIL")
                print(f"    [{status}]  {label}")
            print()

        else:
            try:
                idx = int(raw) - 1
                if not (0 <= idx < len(pairs)):
                    raise ValueError
            except ValueError:
                print(red(f"  Invalid input: '{raw}'"))
                continue

            pair = pairs[idx]
            print(bold(f"\n  -- {pair.label()} --"))

            wave_answer = input("  Open waveform in GTKWave after simulation? [Y/n]: ").strip().lower()
            open_wave   = wave_answer in ("", "y", "yes")

            run_simulation(pair, open_wave=open_wave)


# ---------------------------------------------
# MAIN
# ---------------------------------------------
def main():
    print_banner()

    script_dir = Path(__file__).resolve().parent
    root       = script_dir

    print(f"  Root : {dim(str(root))}")
    print(f"  OS   : {dim(platform.system())} {dim(platform.release())}")
    print()

    # Step 1: Environment
    print(bold("  [1/3] Checking environment ..."))
    tools_ok = ensure_tools()
    if not tools_ok:
        print(yellow("\n  Continuing anyway -- compilation may fail if tools are missing."))

    # Step 2: Discovery
    print()
    print(bold("  [2/3] Discovering simulation pairs ..."))
    pairs = discover_pairs(root)

    if not pairs:
        print(red(f"\n  No simulation pairs found under: {root}"))
        print(red(f"  Expected structure:  <project>/{IMPL_FOLDER_NAME}/<n>.v + <n>_tb.v"))
        sys.exit(1)

    print(green(f"  Found {len(pairs)} pair(s):\n"))
    for proj, group in groupby(pairs, key=lambda p: p.project):
        items = list(group)
        print(f"    {bold(yellow(proj))}")
        for p in items:
            print(f"      . {p.dut_name}")
    print()

    # Step 3: Interactive menu
    print(bold("  [3/3] Entering interactive menu ..."))
    interactive_loop(pairs, root)


if __name__ == "__main__":
    main()
