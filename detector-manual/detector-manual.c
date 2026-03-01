// ============================================================
//  detector-manual.c
// ------------------------------------------------------------
//  When you build your own hardware, you build your own rules.
//  This machine does not follow any existing pattern detection
//  standard. It was designed from scratch, evolving from a
//  simple binary pixel filter into a scoring-based detector
//  isomorphic to the McCulloch-Pitts Neuron.
//
//  This program is that reference. A manual baked directly
//  into the toolchain so the detector architecture is always
//  one command away, no browser, no file explorer, just run
//  it and get your answer.
//
//  Every time the hardware evolves, the logic evolves.
//  Every time the logic evolves, this manual evolves.
// ------------------------------------------------------------
//  Project  : Gate Level Perceptron - Pattern Detector
//  File     : detector-manual.c
//  Covers   : Detector-V0.0, V0.1, V0.2, V1.0
//  Author   : KARAN-D05
//  Date     : 2026
// ============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ─────────────────────────────────────────
// COMPONENT DATABASE (for search)
// ─────────────────────────────────────────

typedef struct {
    char name[30];
    char version[20];
    char function[200];
    char note[200];
} Component;

Component components[] = {
    {
        "Input Grid",
        "V0.0+",
        "A 4x4 grid used to input the pattern, visible through the LED grid.",
        "Arc is the input grid element where 3<=r<=0 and 3<=c<=0. A-W link exists between each element of input grid and weight grid Arc-Wrc."
    },
    {
        "Weight Grid",
        "V0.0+",
        "A 4x4 grid used to configure the machine for detection of a particular pattern.",
        "Uses AND gates with binary weight pins. Acts as a filter -- only allows input through if corresponding weight is 1. Wrc is the weight grid element."
    },
    {
        "Output Grid",
        "V0.0+",
        "A 4x4 grid that shows filtered output. Orc = Arc AND Wrc.",
        "Output is the result of AND between input and weight at each pixel position."
    },
    {
        "Decision Maker",
        "V0.0+",
        "The brain of the machine. Decides if the input pattern is recognized or not.",
        "V0.0: checks equivalence between Input Grid and Output Grid. V0.1: checks equivalence between Weight Grid and Output Grid. V0.2: combines both POVs. V1.0: compares population count M against threshold θ."
    },
    {
        "XNOR Grid",
        "V0.0+",
        "A 4x4 grid of 16 XNOR logic gates. Each gate performs Arc XNOR Orc.",
        "XNOR goes high if both inputs are equal -- a pixel match. Outputs fed into population counter in V1.0."
    },
    {
        "Logical Analyzer",
        "V0.2+",
        "Final decision stage in V0.2 that combines outputs R0 and R1 from both POVs.",
        "R0R1 -> Equivalence | R̄0R1 -> Super-pattern | R0R̄1 -> Sub-pattern | R̄0R̄1 -> Anti-pattern"
    },
    {
        "Population Counter",
        "V1.0",
        "Counts total number of matched pixels M. Built from 64 half-adders.",
        "Based on successive bit compression. 8 half-adders split 16 inputs into SUM and CARRY bits. Wallace Tree based parallel reduction used for faster computation."
    },
    {
        "Threshold",
        "V1.0",
        "Configurable threshold θ set via T-pins. Range: 0 (0000) to 15 (1111).",
        "T-pins are T8 T4 T2 T1. Example: 1001 sets threshold to 9. Pattern recognized if M > θ."
    },
    {
        "MCP Neuron",
        "V1.0",
        "McCulloch-Pitts Neuron model. Sums binary inputs and fires if sum exceeds threshold.",
        "Pop-counter = Cell Body | XNOR inputs = Dendrites | Decision Maker = Signal firing | Output LED = Axon. The detector subsystem is isomorphic to the MCP Neuron."
    },
    {
        "Sub-pattern",
        "V0.0+",
        "Input pattern is a subset of the weight pattern. Arc is a subset of Wrc.",
        "Recognized by V0.0 but not V0.1. In V0.2 identified as sub-pattern via R0 R̄1."
    },
    {
        "Super-pattern",
        "V0.1+",
        "Input pattern is a superset of the weight pattern. Arc is a superset of Wrc.",
        "Recognized by V0.1 but not V0.0. In V0.2 identified as super-pattern via R̄0 R1."
    },
    {
        "Equivalence",
        "V0.0+",
        "Input pattern exactly matches the weight pattern. Arc = Wrc.",
        "Recognized by both V0.0 and V0.1. In V0.2 identified as equivalence via R0 R1."
    },
    {
        "Anti-pattern",
        "V0.2+",
        "Input is neither sub-pattern nor super-pattern nor equivalence of weight pattern.",
        "Arc is not a subset of Wrc AND Wrc is not a subset of Arc. Identified in V0.2 via R̄0 R̄1."
    },
    {
        "Half Adder",
        "V1.0",
        "Basic building block of the population counter. Has SUM and CARRY outputs.",
        "If weight of SUM output is W then weight of CARRY output is 2W. 64 half-adders make up the full population counter."
    },
};

int component_count = 14;

// ─────────────────────────────────────────
// SEARCH HELPER
// ─────────────────────────────────────────

void to_upper(char *str) {
    for (int i = 0; str[i]; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
}

// ─────────────────────────────────────────
// SEARCH FUNCTION
// ─────────────────────────────────────────

void search(char *query) {
    char q[50];
    strncpy(q, query, 49);
    q[49] = '\0';
    to_upper(q);

    int found = 0;

    printf("\n+--------------------------------------------------+\n");
    printf("  Search results for: %s\n", q);
    printf("+--------------------------------------------------+\n");

    for (int i = 0; i < component_count; i++) {
        char name_upper[30];
        char func_upper[200];
        char note_upper[200];

        strncpy(name_upper, components[i].name,     29);  name_upper[29]  = '\0';
        strncpy(func_upper, components[i].function, 199); func_upper[199] = '\0';
        strncpy(note_upper, components[i].note,     199); note_upper[199] = '\0';

        to_upper(name_upper);
        to_upper(func_upper);
        to_upper(note_upper);

        if (strstr(name_upper, q) ||
            strstr(func_upper, q) ||
            strstr(note_upper, q)) {

            printf("\n  Component : %s\n", components[i].name);
            printf("  Version   : %s\n",   components[i].version);
            printf("  Function  : %s\n",   components[i].function);
            printf("  Notes     : %s\n",   components[i].note);
            printf("\n  --------------------------------------------------\n");
            found++;
        }
    }

    if (found == 0)
        printf("\n  No results found for '%s'\n", q);
    else
        printf("\n  %d result(s) found.\n", found);

    printf("+--------------------------------------------------+\n");
}

// ─────────────────────────────────────────
// VERSION MANUALS
// ─────────────────────────────────────────

void manual_v00() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|         Detector-V0.0 - Binary Pixel Filter          |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" A primitive configurable pattern detection machine\n");
    printf(" built entirely from logic gates. Uses a weight array\n");
    printf(" to filter the input pattern and a decision-making\n");
    printf(" stage to check recognition.\n");
    printf(" Recognizes exact match and sub-patterns.\n");
    printf(" Problem: also recognizes garbage/sub-patterns.\n");

    printf("\n COMPONENTS\n");
    printf(" ----------\n");

    printf("\n [1] Input Grid (4x4)\n");
    printf("     Arc is the input grid element (3<=r<=0, 3<=c<=0)\n");
    printf("     A-W link connects each Arc to its Wrc.\n");

    printf("\n [2] Weight Grid (4x4)\n");
    printf("     Wrc is the weight grid element.\n");
    printf("     AND gates with binary weight pins.\n");
    printf("     Acts as a filter: passes input only if weight=1.\n");

    printf("\n [3] Output Grid (4x4)\n");
    printf("     Orc = Arc AND Wrc\n");
    printf("     Shows the filtered result of input through weight.\n");

    printf("\n [4] Decision Maker\n");
    printf("     Checks equivalence between Input Grid and Output Grid.\n");
    printf("     XNOR check: (A00^O00) AND (A01^O01) AND ... AND (A33^O33)\n");
    printf("     Result = 1 -> Pattern recognized\n");
    printf("     Result = 0 -> Pattern not recognized\n");
    printf("     Recognized if: Arc is a subset of Wrc\n");
    printf("     Not Recognized if: Arc is not a subset of Wrc\n");

    printf("\n LIMITATIONS\n");
    printf(" -----------\n");
    printf("     * Also recognizes sub-patterns and garbage patterns.\n");
    printf("     * No scoring or noise tolerance.\n");
    printf("     * Expects perfectly clean inputs.\n");
    printf("     * Binary pixel filter + comparator only.\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v01() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|      Detector-V0.1 - Super-Pattern Recognition       |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" Solves the sub-pattern recognition problem of V0.0.\n");
    printf(" Instead of recognizing sub-patterns, it now correctly\n");
    printf(" recognizes the exact pattern and super-patterns.\n");
    printf(" Single architectural change in the Decision Maker.\n");

    printf("\n COMPONENTS\n");
    printf(" ----------\n");

    printf("\n [1] Input Grid (4x4)  -- same as V0.0\n");
    printf(" [2] Weight Grid (4x4) -- same as V0.0\n");
    printf(" [3] Output Grid (4x4) -- same as V0.0\n");
    printf("     Orc = Arc AND Wrc\n");

    printf("\n [4] Decision Maker (changed from V0.0)\n");
    printf("     Now checks equivalence between Weight Grid and\n");
    printf("     Output Grid (NOT Input vs Output like V0.0).\n");
    printf("     Sets a lower bound below which pattern cannot\n");
    printf("     be recognized.\n");
    printf("     XNOR check: (W00^O00) AND (W01^O01) AND ... AND (W33^O33)\n");
    printf("     Result = 1 -> Pattern recognized\n");
    printf("     Result = 0 -> Pattern not recognized\n");

    printf("\n MATHEMATICAL BEHAVIOUR\n");
    printf(" ----------------------\n");
    printf("     Recognized:\n");
    printf("       Orc = Wrc\n");
    printf("       Orc is subset of Arc\n");
    printf("       Wrc is subset of Arc\n");
    printf("     Not Recognized:\n");
    printf("       Orc != Wrc\n");
    printf("       Orc is not subset of Arc\n");
    printf("       Wrc is not subset of Arc\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v02() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|       Detector-V0.2 - Four-Way Pattern Classifier    |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" Combines V0.0 and V0.1 as two independent POVs.\n");
    printf(" Classifies input into one of four categories:\n");
    printf("   Equivalence, Sub-pattern, Super-pattern, Anti-pattern\n");

    printf("\n MECHANISM\n");
    printf(" ---------\n");
    printf("     V0.0 POV (R0): Recognizes Equivalence + Sub-patterns\n");
    printf("     V0.1 POV (R1): Recognizes Equivalence + Super-patterns\n");

    printf("\n LOGICAL ANALYZER (Final Decision Stage)\n");
    printf(" ----------------------------------------\n");
    printf("     R0  AND R1  -> Equivalence  (Arc = Wrc)\n");
    printf("     R0  AND R1' -> Sub-pattern  (Arc is subset of Wrc)\n");
    printf("     R0' AND R1  -> Super-pattern (Arc is superset of Wrc)\n");
    printf("     R0' AND R1' -> Anti-pattern (no subset/superset relation)\n");

    printf("\n PATTERN DEFINITIONS\n");
    printf(" -------------------\n");
    printf("     Equivalence  : Arc = Wrc\n");
    printf("     Sub-pattern  : Arc is proper subset of Wrc\n");
    printf("     Super-pattern: Arc is proper superset of Wrc\n");
    printf("     Anti-pattern : Arc not subset/superset of Wrc\n");
    printf("                    or Arc intersection Wrc = empty\n");

    printf("\n LIMITATIONS\n");
    printf(" -----------\n");
    printf("     * No learning or adaptation.\n");
    printf("     * Weight grid is fixed, never changes.\n");
    printf("     * No generalization for shifted patterns.\n");
    printf("     * Rigid decision boundaries.\n");
    printf("     * No memory of past inputs.\n");
    printf("     * Embedded intelligence -- can reason but not improve.\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v10() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|     Detector-V1.0 - POP-Count Based Detector         |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" Replaces exact equivalence check with a scoring system.\n");
    printf(" Counts matched pixels M using a population counter\n");
    printf(" and compares against an adjustable threshold θ.\n");
    printf(" Isomorphic to the McCulloch-Pitts (MCP) Neuron.\n");
    printf(" One step closer to self-learning machines.\n");

    printf("\n COMPONENTS\n");
    printf(" ----------\n");

    printf("\n [1] XNOR Equivalence Grid (4x4)\n");
    printf("     16 XNOR gates. Each gate: Arc XNOR Orc\n");
    printf("     Gate goes high if both inputs are equal (pixel match).\n");
    printf("     Outputs fed into the population counter.\n");
    printf("     Biologically equivalent to: Dendrites\n");

    printf("\n [2] Population Counter\n");
    printf("     Counts total matched pixels M.\n");
    printf("     Built from 64 half-adders.\n");
    printf("     Based on successive bit compression principle:\n");
    printf("       8 HA -> 8 SUM bits (weight 1) + 8 CARRY bits (weight 2)\n");
    printf("       4 HA -> further compresses SUM bits of weight 1\n");
    printf("       Repeats until single bit of each weight remains.\n");
    printf("     Wallace Tree used for parallel faster reduction.\n");
    printf("     Biologically equivalent to: Cell Body\n");

    printf("\n [3] Decision Maker\n");
    printf("     Compares M against threshold θ.\n");
    printf("     Pattern Recognized     : M > θ\n");
    printf("     Pattern Not Recognized : M <= θ\n");
    printf("     Priority-Encoded Magnitude Comparator.\n");
    printf("     Biologically equivalent to: Signal firing decision\n");

    printf("\n [4] Threshold (T-pins)\n");
    printf("     Set via T8 T4 T2 T1 pins.\n");
    printf("     Range: 0 (0000) to 15 (1111)\n");
    printf("     Example: 1001 -> threshold = 9\n");
    printf("     Adjustable for confidence tuning.\n");

    printf("\n [5] Output LED\n");
    printf("     Fires if M > θ.\n");
    printf("     Biologically equivalent to: Axon\n");

    printf("\n MCP NEURON ISOMORPHISM\n");
    printf(" ----------------------\n");
    printf("     XNOR inputs (16)  <->  Dendrites\n");
    printf("     Population Counter <->  Cell Body\n");
    printf("     Decision Maker     <->  Signal firing (threshold)\n");
    printf("     Output LED         <->  Axon\n");

    printf("\n THRESHOLD EXAMPLES\n");
    printf(" ------------------\n");
    printf("     θ=7, M=8 : M > θ -> Pattern RECOGNIZED\n");
    printf("     θ=9, M=8 : M <= θ -> Pattern NOT RECOGNIZED\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_all() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|         Detector Manual - All Versions               |\n");
    printf("+------------------------------------------------------+\n");
    printf("\n  V0.0 -> Binary pixel filter, recognizes sub-patterns\n");
    printf("  V0.1 -> Fixes V0.0, recognizes super-patterns\n");
    printf("  V0.2 -> Four-way classifier using both POVs\n");
    printf("  V1.0 -> POP-Count based, MCP Neuron isomorphic\n");
    printf("\n Showing all versions...\n");
    manual_v00();
    manual_v01();
    manual_v02();
    manual_v10();
}

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────

int main(int argc, char *argv[]) {

    // ./detector-manual --search threshold
    if (argc >= 3 && strcmp(argv[1], "--search") == 0) {
        search(argv[2]);
        return 0;
    }

    // ./detector-manual --search (no query)
    if (argc == 2 && strcmp(argv[1], "--search") == 0) {
        printf("Usage: ./detector-manual --search <term>\n");
        printf("Example: ./detector-manual --search threshold\n");
        return 1;
    }

    // interactive mode
    char input[20];

    printf("+------------------------------------------------------+\n");
    printf("|           Gate Level Perceptron Manual               |\n");
    printf("|         Pattern Detector Architecture Docs           |\n");
    printf("+------------------------------------------------------+\n");
    printf(" Tip: search a component directly from terminal:\n");
    printf("      ./detector-manual --search threshold\n");

    while (1) {
        printf("\n Available: V0.0 | V0.1 | V0.2 | V1.0 | all | search | exit\n");
        printf(" Enter version: ");
        scanf("%s", input);

        if (strcmp(input, "V0.0") == 0 || strcmp(input, "v0.0") == 0) {
            manual_v00();
        } else if (strcmp(input, "V0.1") == 0 || strcmp(input, "v0.1") == 0) {
            manual_v01();
        } else if (strcmp(input, "V0.2") == 0 || strcmp(input, "v0.2") == 0) {
            manual_v02();
        } else if (strcmp(input, "V1.0") == 0 || strcmp(input, "v1.0") == 0) {
            manual_v10();
        } else if (strcmp(input, "all") == 0) {
            manual_all();
        } else if (strcmp(input, "search") == 0) {
            char query[50];
            printf(" Enter term to search: ");
            scanf("%s", query);
            search(query);
        } else if (strcmp(input, "exit") == 0) {
            printf("\n Goodbye!\n");
            break;
        } else {
            printf("\n [ERROR] Unknown input '%s'\n", input);
            printf(" Try: V0.0, V0.1, V0.2, V1.0, all, search, exit\n");
        }
    }

    return 0;
}
