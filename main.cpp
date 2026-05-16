#include "src/App.h"
#include "src/Sys.h"

int main() {
    Carpet::App carpet(
        // Sys::GetMonitorSize()
        { 1536, 864 }
    );
    while (carpet.Run()) {}
    return 0;
}
