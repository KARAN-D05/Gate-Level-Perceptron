Write-Host "+--------------------------------------------------+"
Write-Host "|      detector-manual - PowerShell Installer      |"
Write-Host "+--------------------------------------------------+"

Write-Host ""
Write-Host "Checking for GCC..."
$gcc = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gcc) {
    Write-Host "[ERROR] GCC not found!"
    Write-Host "  Download MinGW from: https://www.mingw-w64.org"
    Write-Host "  Then add C:\MinGW\bin to your system PATH."
    exit 1
}
Write-Host "[OK] GCC found."

Write-Host ""
Write-Host "Downloading detector-manual.c from GitHub..."
try {
    Invoke-WebRequest `
        -Uri "https://raw.githubusercontent.com/KARAN-D05/Assembler/main/detector-manual/detector-manual.c" `
        -OutFile "detector-manual.c" `
        -ErrorAction Stop
    Write-Host "[OK] Download complete."
} catch {
    Write-Host "[ERROR] Download failed. Check your internet connection."
    exit 1
}

Write-Host ""
Write-Host "Compiling..."
gcc detector-manual.c -o detector-manual.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "[ERROR] Compilation failed."
    exit 1
}
Write-Host "[OK] Compilation successful."

Write-Host ""
Write-Host "Launching detector-manual..."
Write-Host "+--------------------------------------------------+"
Write-Host ""
.\detector-manual.exe
