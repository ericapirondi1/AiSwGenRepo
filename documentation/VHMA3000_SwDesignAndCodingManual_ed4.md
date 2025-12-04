# VHMA 3000 — SW Design and Coding Manual (4th issue, 11/2025)

**Document code:** VHMA3000  
**Title:** SW Design and Coding Manual  
**Created by:** VHIT/EAD13  
**Issue:** 4th  
**Date:** 11/2025  

---

## Content

### General coding guidelines

All the rules listed in the next paragraphs can be classified as derivatives of the following macro‑rules:

- **The code shall be maintainable and easy to read**  
  As code will be further developed from other developers no error‑prone or difficult to understand code shall be implemented.

- **The code shall be compiler independent as far as possible**  
  Code re‑use (especially core modules) shall be maximized.

- **The code shall be microcontroller independent as far as possible**  
  Code re‑use (especially core modules) shall be maximized.  
  The rule is particularly intended for Application SW, whose interfaces toward uC shall be kept separated in a different file. Device drivers are excluded for obvious reasons.

- **The code shall be MISRA 2012 compliant**  
  Advisory rules compliance is not mandatory but recommended.

- **The code shall respect the metrics (HIS) defined in table**

- **The code shall be documented in a way to be parsed by Doxygen**  
  Doxygen is a powerful tool to document the code and is used by VHIT/EAD for this purpose.

---

## Style guide

### SDCM_0001 — File header information

**Scope:** File header information  
**Description:** Every source file shall be headed by the standard header file.

**Example:**

```c
/***************************************************************************//**
 * \file           file_name.c
 * \brief          Description
 * \author         EAD1 SW Team – Author
 * \date           02/11/2022
 *
 * \par            Copyright (c) 2022, VHIT S.p.A. All rights reserved
 * 
 * \defgroup       ModuleName    Group Name
 * @{
 ******************************************************************************/
```

**Version:** V_001

---

### SDCM_0002 — Comments in C source code

**Scope:** Comments in C source code  
**Description:**

- Following comment marks are allowed: `/* ... */` and `//`.
- Code sections that are not self‑explanatory shall be extended by a meaningful comment.
- Comments in the source code shall be written in English.
- The comment is aligned at the code to which it belongs.
- Nesting of comments is not allowed. Tools might handle nested comments in a different way.
- Meaningful comments shall follow Doxygen style.

**Version:** V_001

---

## Programming guide

### Preprocessor directives

#### SDCM_0003 — Numeric constants

**Scope:** Numeric constants  
**Description:** Macros shall be used for symbolic numeric constants.  
**Version:** V_001

---

#### SDCM_0004 — Function‑like macros

**Scope:** Function‑like macros  
**Description:** Function‑like macros shall be avoided unless they provide a significant improvement in terms of performance. Anyway, if possible, inline functions shall be used instead of function‑like macro.

**Note:** Function remapping is not affected by this rule. It allows advantages in terms of reusability and configurability.  
**Version:** V_001

---

#### SDCM_0005 — Macros usage

**Scope:** Macros usage  
**Description:**

- Macros can be used to realize accesses to structures, generate bit masks or to realize small and easy logical or mathematical operations.
- Macros must not be used to replace keywords or constructs of the language C. This is required for readability and maintainability of the code.
- Macro body and macro parameters must be enclosed in parentheses (if macro is not only a define for a symbolic numeric constants).
- Every macro call shall not be completed with a semicolon; semicolons have to be set outside the macro.

**Version:** V_001

---

### Function prototypes

#### SDCM_0006 — Interface visibility

**Scope:** Interface visibility  
**Description:** Separate interfaces into public and private header files and make the visibility explicit by naming of the source file.  
Example: define all private interfaces in `*_priv.h` and `*_api.h` for global.  
**Version:** V_001

---

#### SDCM_0007 — Function declaration

**Scope:** Function declaration  
**Description:** Every function shall have a function declaration in the corresponding header file (C++ compatibility).  
**Version:** V_001

---

#### SDCM_0008 — Function prototype identifiers

**Scope:** Function declaration  
**Description:** Function prototype declarations shall contain also the parameter identifiers to increase readability and maintainability of the code.  
**Version:** V_001

---

### Const

#### SDCM_0009 — Constant variables

**Scope:** Constant variables  
**Description:** Variables and parameters that will not change shall be declared with `const` qualifier.  
**Version:** V_001

---

#### SDCM_0010 — Function inputs

**Scope:** Function inputs  
**Description:** Function inputs are constant in the function scope, so they shall be declared with `const` qualifier.  
**Version:** V_001

---

### Local variables

For different use cases in a function, different local variables shall be used. Re‑use of local variables is error‑prone and shall be avoided. Use several local variables shouldn’t impact too much the resources usage because compiler can optimize the code based on register variables. In most cases, local variables are located in registers of the processor.

#### SDCM_0011 — Local variables name

**Scope:** Local variables name  
**Description:** Local variable names shall start with the prefix `l_` followed by a meaningful name.  
**Version:** V_001

---

#### SDCM_0012 — Local variables usage

**Scope:** Local variables usage  
**Description:** Don’t re‑use variables for different purposes.  
**Version:** V_001

---

#### SDCM_0013 — Local variables type

**Scope:** Local variables type  
**Description:** Local variables type shall always be 32 bit. Avoid to use smaller types. Arm compiler produce more efficient code using 32 bit variables.

The possible increase of stack usage shall be avoided reducing the calling hierarchy depth and considering that Arm compiler uses registers (if available) for local variables.

**Version:** V_001

---

### Data types

#### SDCM_0014 — Data type for persistent variables

**Scope:** Data type for persistent variables  
**Description:** The smallest integer type which holds the required value range shall be used for variables which use storage (global variables, static variables, parameters).  
**Version:** V_001

---

#### SDCM_0015 — 64‑bit types

**Scope:** 64‑bit types  
**Description:** 64‑bit integer shall be avoided (we are on a 32‑bit architecture) or used only in exceptional cases.  
**Version:** V_001

---

#### SDCM_0016 — Positive types

**Scope:** Positive types  
**Description:** If the possible value range of the variable are only positive values, then an unsigned type should be chosen.  
**Version:** V_001

---

#### SDCM_0017 — Floating point

**Scope:** Floating point  
**Description:** Floating point type shall be used only if they are strictly necessary. This rule shall not be applied for uCs equipped with a FPU.  
**Version:** V_001

---

#### SDCM_0018 — Bit masks

**Scope:** Bit masks  
**Description:** For variables which hold bit masks or bit strings an unsigned type shall be used.  
**Version:** V_001

---

#### SDCM_0019 — Bit fields type

**Scope:** Bit fields type  
**Description:** Bitfields shall be declared as `int` (or its equivalent) type.  
**Version:** V_001

> From compiler manufacturer you may find following statements:  
> “In general, the use of the variables of size int is beneficial for both the run time and code size. The effect is about 5% better code density and a similar run time improvement.”  
> This statement should only be taken into account in case when highly efficient code shall be written regarding run time and code (e.g. centrally called services). For normal application software the rules for size and signedness shall be followed in order to save RAM, which in most cases is the more critical resource.

---

### User defined data types — typedefs

#### SDCM_0020 — Project specific typedefs

**Scope:** Project specific typedefs  
**Description:** Project specific typedefs shall not be used to define new names for the existing standard types.  
**Version:** V_001

---

#### SDCM_0021 — Bit fields

**Scope:** Bit fields  
**Description:** For portability reasons C bit fields should not be used, unless they are strictly necessary.  
**Version:** V_001

---

#### SDCM_0022 — Unions

**Scope:** Unions  
**Description:** For portability reasons, unions shall be avoided when possible.

**Hint:** if unions are needed (e.g. to access registers) encapsulate them in an abstraction layer.  
**Version:** V_001

---

### Constructs

#### SDCM_0024 — Constructs

**Scope:** Constructs  
**Description:** For portability reasons, the code shall be compiler independent. VHIT code could be potentially used for different uCs and compiled with different compilers.  
**Version:** V_001

---

### Statements

#### SDCM_0025 — Likely‑first ordering in selections

**Scope:** Statements  
**Description:** In selection statements (e.g., if‑else), the more likely condition should be placed in the first clause, followed by other conditions in descending order of likelihood.  
**Version:** V_001

---

#### SDCM_0028 — Bounded iterations

**Scope:** Statements  
**Description:** Iteration statements (for, while, do‑while) shall have a predetermined maximum number of iterations. Exceptions are allowed only with a proper justification.  
**Version:** V_001

---

#### SDCM_0030 — Timeouts in event‑waiting loops

**Scope:** Statements  
**Description:** Iteration statements waiting for an event shall have a timeout breaking the loop. If the timeout occurs, the behavior shall be handled.  
**Version:** V_001

---

#### SDCM_0031 — Inequalities for loop termination

**Scope:** Statements  
**Description:** All iterative loop terminations shall use inequalities (`<`, `<=`, `>`, `>=`) and there shall be a check for range plausibility.  
**Version:** V_001

---

### Comments

#### SDCM_0026 — Comment complex computations

**Scope:** Comments  
**Description:** The source code must be commented on all computations that include at least five variables or parameters about the meaning or logic.  
**Version:** V_001

---

#### SDCM_0027 — Comment each variable definition

**Scope:** Comments  
**Description:** Each variable definition must be commented with its meaning and usage.  
**Version:** V_001

---

### Compiler Independency

#### SDCM_0023 — Compiler independency

**Scope:** Compiler Independency  
**Description:** For portability reasons, the code shall be compiler independent. VHIT code could be potentially used for different uCs and compiled with different compilers.  
**Version:** V_001

---

### SW Behavior

#### SDCM_0029 — Reset vector jumps

**Scope:** SW behavior  
**Description:** Jumps to the Reset Vector shall not be used. Exceptions to the rule are allowed only if properly justified.  
**Version:** V_001

---

## Interrupt Service Routines (ISR)

### ISR Design and Execution

#### SDCM_ISR_001 — Deterministic ISR duration

**Scope:** Interrupts  
**Description:** An Interrupt Service Routine (ISR) shall execute in a deterministic and time‑bounded manner, not exceeding the maximum allowed execution time defined by system timing constraints.  
**Version:** V_001

---

#### SDCM_ISR_002 — Avoid blocking/time‑consuming operations

**Scope:** Interrupts  
**Description:** The ISR shall not contain blocking or time‑consuming operations, including dynamic memory allocation, I/O operations, or delay loops.  
**Version:** V_001

---

#### SDCM_ISR_003 — Minimal ISR processing

**Scope:** Interrupts  
**Description:** The ISR shall only perform minimal processing and shall defer complex logic to background tasks via signaling mechanisms, optimizing it by time execution.  
**Version:** V_001

---

### Shared Data and Concurrency

#### SDCM_ISR_004 — Volatile shared variables

**Scope:** Interrupts  
**Description:** All variables shared between ISRs and non‑interrupt code shall be declared with the `volatile` keyword to prevent compiler optimization issues.  
**Version:** V_001

---

#### SDCM_ISR_005 — Protect shared resources

**Scope:** Interrupts  
**Description:** Access to shared resources between ISRs and main code shall be protected using atomic operations or critical sections to prevent race conditions.  
**Version:** V_001

---

#### SDCM_ISR_006 — Avoid priority inversion

**Scope:** Interrupts  
**Description:** Interrupt nesting and priority levels shall be configured to avoid priority inversion and ensure timely execution of critical ISRs.  
**Version:** V_001

---

#### SDCM_ISR_007 — Document ISRs

**Scope:** Interrupts  
**Description:** All ISRs shall be documented with their expected behavior, priority, and fault handling strategy.  
**Version:** V_001

---

### Global Interrupt Disable Handling

#### SDCM_ISR_008 — Ensure re‑enable

**Scope:** Interrupts  
**Description:** The system shall ensure that no exception, error, or unexpected control flow can prevent the re‑enabling of interrupts after a critical section.  
**Version:** V_001

---

#### SDCM_ISR_009 — Keep critical sections simple

**Scope:** Interrupts  
**Description:** When global interrupts are disabled to protect critical sections, the code block shall not contain any conditional branches, loops, or function calls that could delay or prevent timely re‑enabling of interrupts.  
**Version:** V_001

---

#### SDCM_ISR_010 — Minimize disable duration

**Scope:** Interrupts  
**Description:** The duration of global interrupt disable shall be minimized and shall not exceed the maximum allowed blocking time defined by system timing constraints.  
**Version:** V_001

---

#### SDCM_ISR_011 — Mark critical sections

**Scope:** Interrupts  
**Description:** Each code block where global interrupts are disabled shall be clearly marked with comments indicating the start and end of the critical section.  
**Version:** V_001

---

#### SDCM_ISR_012 — Review/justify uses

**Scope:** Interrupts  
**Description:** All uses of global interrupt disable shall be reviewed and explicitly justified.  
**Version:** V_001

---

## Annex 1 — Code metrics

### Source Code Metrics

The source code metrics are valid for the programming language **C**. These must be adopted analogously for other programming languages.

If source code metric deviations or boundary value violations are necessary because of project specific reasons, these must be evaluated on unit level and documented including comprehensible justifications.

In case of source code metric deviations or boundary value violations appropriate measures must be applied to ensure the software quality.

**Metrics and limits**

- **COMF** — Ratio between the number of comments (outside and inside the functions) to the number of statements must be **greater than 0.2**.  
  This requirement is applied for source code manually written; for code automatically generated the rule will not be applied.

- **PATH** — Number of non‑cyclic execution paths must be **≤ 80**.  
  Static analysis tools overestimate real paths; in case of violation, the result shall be demonstrated.

- **GOTO** — Number of unconditional jumps must be **0**.

- **v(G)** — Cyclomatic complexity must be **≤ 10**.

- **PARAM** — Number of function parameters must be **≤ 5**.

- **STMT** — Number of statements in a function must be **≤ 50 and > 0**.  
  Some violations can be justified by particular design choices; provide justification if needed.

- **LEVEL** — Number of nested levels inside a function must be **≤ 4**.

- **RETURN** — Number of return statements in a function must be **0 or 1**.

- **Recursions** — Number of recursions must be **0**.

- **VOCF** — Vocabulary frequency must be **≤ 4**.  
  It can be violated due to a specific design choice; provide proper justification.

---