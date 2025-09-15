# CPA Tracker

## 📌 Introduction
CPA Tracker is a cross-platform desktop application (Windows / macOS / Linux) built with **C++ & Qt**.  
It allows students to manage and calculate their **Course Performance Average (CPA)** easily, with features like:
- Add, edit, and remove courses.
- Manage grades (with GPA scale 0.0 – 4.0 and alphabet mapping).
- Search courses by **Code** or **Name**.
- Sort courses (by Code using HeapSort, or Name using IntroSort).
- Import/export course list to CSV files.
- Cross-platform support (Qt6 + CMake).

---

## 🚀 Getting Started

### Prerequisites
- **Qt 6.6.0+**
- **CMake 3.20+**
- C++17 compiler (GCC / Clang / MSVC)

Download below here:
- [Qt 6](https://www.qt.io/download)
- [CMake](https://cmake.org/download/)
- [Git](https://git-scm.com/)

---

## 💻 Usage

### 1. Via Release Link
- Download pre-built binaries from the [Releases](https://github.com/ghosteater1311/CPA_Tracker/releases).
- Extract and run the executable for your OS.

### 2. Manually Build Program in Console
Clone the repo:
```sh
git clone https://github.com/ghosteater1311/CPA_Tracker.git
cd CPA_Tracker
```

Build:
```sh
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$Qt6_DIR
cmake --build . --config Release
```

Run:
```sh
./cpatracker    # Linux / macOS
cpatracker.exe  # Windows
```

### Setting Up
* Import courses from a CSV file, or create a new table directly.
* Add / Edit / Remove courses from the menu bar.
* Save changes via File → Save / Save As.

### Initialize 
When first run:
* If no file is loaded → CPA Tracker acts like a new sheet.
* You can add courses manually or import a CSV.

### Explaination
* Code: Course code (e.g., CS101).
* Name: Full course name.
* Credits: Number of credits (1–5).
* Grade: GPA scale (0.0–4.0).
* Alphabet: Auto-mapped grade (A, B, C, etc.).

### Demo


<!-- LICENSE -->
## 📜 License
Distributed under the GPL-3.0 license. 
See `LICENSE.txt` for more information.

<!-- CONTACT -->
## 📬 Contact
For further information, reviews, comments or issues:
* GitHub: [ghosteater1311](https://github.com/ghosteater1311)
* Email: _nda27092005@gmail.com_

Thank you so much for supporting this project ❤️

<!-- ACKNOWLEDGMENTS -->
## 🙏 Acknowledgments
* [Qt Framework](https://www.qt.io/)
* [CMake](https://cmake.org/)
* [GitHub Actions CI/CD for cross-platform build](https://github.com/features/actions)
