# Renesas/RH850 - Embedded Platform Project

This repository demonstrates an automotive-grade embedded software platform developed on the Renesas RH850/P1M microcontroller family using the CS+ IDE.
The project showcases professional practices in driver development, safety supervision, task scheduling, and modular architecture, following AUTOSAR-inspired concepts.

📂 Project Structure
- `rh850-p1m-embedded-platform.mtpj` – CS+ project file (open this to load the project in CS+ IDE).
-*.c, *.h, *.asm – Source code and headers for drivers, tasks, safety monitoring, and system initialization.

README.md – Project documentation.

LICENSE – License information.

✨ Key Features

CAN Communication: Configured with TJA1145 transceiver for reliable in-vehicle networking.

SPI Master Drivers: Implemented CSIH0 and CSIG0 interfaces with CRC-6 error detection for robust peripheral communication.

Watchdog Manager (WdgM): Integrated periodic service routines to supervise tasks and ensure system safety.

Task Scheduler (SchM): Cooperative multi-rate scheduler executing 2 ms, 5 ms, and 10 ms tasks deterministically.

System Initialization: Modular bring-up of clocks, interrupts, and diagnostics for predictable ECU startup.

AUTOSAR-Inspired Architecture: Clear layering between Application, Scheduler, Drivers, and Hardware Abstraction for scalability and maintainability.

🔧 Technical Highlights

~52,000 lines of code (including device headers).

~44% documentation coverage across source files.

34 source/header files organized by functional domain.

Modular structure aligned with AUTOSAR concepts (SchM, WdgM, Com stack layering).

Designed for reusability, scalability, and professional demonstration.

⚙️ Requirements

Renesas CS+ IDE

RH850/P1M microcontroller (or compatible device)

Toolchain: Renesas C Compiler for RH850
---

## ⚙️ Requirements
- **Renesas CS+ IDE**  
- **RH850/P1M** microcontroller (or compatible family)  
- Toolchain: Renesas C Compiler for RH850  

---

## 🚀 How to Use
1. Clone or download this repository.
2. Open `rh850-p1m-embedded-platform.mtpj` in CS+ IDE.
3. Build the project.
4. Flash the compiled binary onto your RH850/P1M target hardware.

---

🏗️ Architecture Overview
+---------------------------+
|        Application        |
+---------------------------+
            |
            v
+---------------------------+
|   Scheduler (SchM)        |
|   Watchdog Manager (WdgM) |
+---------------------------+
            |
            v
+---------------------------+
|   Drivers (CAN, SPI)      |
+---------------------------+
            |
            v
+---------------------------+
|   Hardware Abstraction    |
|   (RH850/P1M, TJA1145)    |
+---------------------------+

## 📜 License
This project is released under the **Educational Use Only License** (see [LICENSE](License)).  
It may be used for **learning, academic, and interview preparation purposes**.  
**Commercial use is not permitted.**

📌 Confidentiality Note

Certain safety-critical implementations (e.g., diagnostics, error reaction strategies) are intentionally omitted due to confidentiality.
The remaining code demonstrates code quality, modular design, and professional practices relevant to automotive embedded systems

