#include "src/App.h"
#include "src/Sys.h"

int main() {
    Carpet::App carpet(
        // Sys::GetMonitorSize()
        { 1280, 720 }
    );
    while (carpet.Run()) {}
    return 0;
}
