Below is a fully rewritten version of your **README.md**, already formatted and ready to replace the existing file.
It includes all your original content from , corrected grammar, improved structure, and a new section explaining the Docker build system and commands.

---

# Project Overview

This project manages unit testing across multiple software modules, updates platform files automatically, executes tests, and generates consolidated test result reports.
It also includes a Docker-based environment for building all modules and performing cppcheck + MISRA static analysis in a reproducible way.

---

## 📂 Project Structure

```
code/                     # Source code for each module
  ├─ cfg/                 # Configuration files
  ├─ pltf/                # Platform files updated by scripts
  └─ unitTests/           # Unit test definitions

mixin/                    # Shared or reusable components

misra/                    # Contains the MISRA headlines file used by cppcheck

utExecutionAndResults/
  ├─ utUnderTest/         # Tests currently being executed
  └─ utResults/
       └─ total_result_report.txt   # Consolidated results of all test runs

Dockerfile                # Build + test + MISRA analysis environment
```

---

## 🧪 UnitTestsLauncher Script Functionality

The `unitTestsLauncher` script performs four main operations:

1. **Collect all test folders**
   Scans all modules and finds folders named `TEST_*` that contain unit tests.

2. **Update platform files**
   Updates the `pltf/` folder of each module to ensure test configurations are synchronized.

3. **Run unit tests**
   Executes all unit tests located in the `unitTests/` directories.

4. **Update the consolidated report**
   After execution, the script creates or updates the report:

```
utExecutionAndResults/utResults/total_result_report.txt
```

This file contains the summary of all executed tests.

---

## 📊 Report Format

The consolidated report table includes:

* **Function Name Under Test** → The function or module being tested
* **Total** → Total number of executed tests
* **Passed** → Number of tests that passed
* **Failed** → Number of tests that failed
* **Ignored** → Number of skipped or disabled tests

The table is aligned so it is easy to read.

---

## 🚀 Usage Workflow

1. Place or update unit test files inside each module’s `unitTests/` folder.
2. Run the script `parsingUtTest.py` from the main project folder using:

```
python parsingUtTest.py all
```

This will:

* Update the `pltf` files
* Execute all unit tests
* Update the consolidated report

3. Review the results:

```
utExecutionAndResults/utResults/total_result_report.txt
```

---

# 🐳 Docker Build + Static Analysis Environment

The repository includes a `Dockerfile` that creates a complete environment for:

* Compiling all CMake-based modules under `code/`
* Running cppcheck on each module
* Performing MISRA C:2012 headline checks via cppcheck’s `misra.py` addon
* Producing XML reports for static analysis

This ensures consistent builds and analysis regardless of the host system.

---

## 🧱 Building the Docker Image

Run this from the project root:

```bash
docker build -t cmake-misra-multi .
```

---

## ▶ Running the Build + MISRA Checks

### **Windows PowerShell**

```powershell
docker run --rm `
  -v "${PWD}:/workspace" `
  cmake-misra-multi `
  build-and-check-all.sh
```

### **Linux / macOS**

```bash
docker run --rm \
  -v "$(pwd):/workspace" \
  cmake-misra-multi \
  build-and-check-all.sh
```

### ✔ What this does

* Mounts your project into the container
* Builds all modules that contain a `CMakeLists.txt`
* Runs any available CTest suites
* Runs cppcheck with MISRA headlines
* Generates XML reports per module

---

## ❗ Notes About MISRA Headlines

The directory:

```
misra/
```

contains the official **MISRA C:2012 Headlines for Cppcheck** file.
Inside the container it is renamed to:

```
/workspace/misra/misra_headlines.txt
```

and used by cppcheck via:

```
--rule-texts=/workspace/misra/misra_headlines.txt
```

This allows cppcheck to display MISRA rule names and descriptions in its output.

---

If you'd like, I can automatically generate badges, a table of contents, or diagrams for the README.
