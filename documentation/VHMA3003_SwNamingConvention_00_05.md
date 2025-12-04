# VHMA 3003 — SW Naming Convention (3rd issue, 08/2023)

**Document code:** VHMA3003  
**Title:** SW Naming Convention  
**Created by:** VHIT/EAD1  
**Issue:** 3rd  
**Date:** 08/2023  

---

## Content

## ASW — MatLab/Simulink

### Signals, parameters and constant

The full name shall be composed of three different parts:

`<type><VariableName>_<datatype>`

The meaning of such parts is explained in the subsequent paragraphs.

#### Description of `<type>`

The naming part `<type>` is used to identify signals, parameters and constants.

In case of **signals**, the type collects information about physical quantity and units of measurement and is composed by a maximum of two consecutive small letters, such as:

- `ad`, representing an angular position measured in **[deg]**
- `ar`, representing an angular position measured in **[rad]**
- `i`, representing an electric current measured in **[A]**

For **parameters** and **constants**, the types are fixed and are:

- `par` for parameters
- `cst` for constants

Since such types do not contain units information, both parameters and constants are defined according to the **International System of Units**.

The list of all possible types for signals can be found in **Table 1**.

#### Description of `<VariableName>`

`<VariableName>` describes more in detail the kind of signal/parameter and is specific for each one.

A `<VariableName>` can be composed by one or more consecutive keywords written with **PascalCasing**:

- each keyword uses small letters except the first one, which is capital
- keywords must not exceed **4 letters**
- they are normally abbreviations of full words

Examples:

- `Curr` → “current”
- `Drvt` → “derivative”
- `Temp` → “temperature”
- `Gain` → “gain” (full word, since shorter than 5 letters)

The list of possible keywords is in **Table 2**.

#### Description of `<datatype>`

`<datatype>` indicates the data type of signal/parameter/constant and how it is converted during code generation.

Fixed‑point C code does not accept non‑integer numbers, so a scaling factor is needed for decimals. The scaling factor is the inverse of the discretization precision in the physical domain.

`<datatype>` is composed by four parts:

`<typesign><typelength><typeprecision><typebias>`

##### Description of `typesign`

Indicates signedness:

- `s` → signed (positive or negative)
- `u` → unsigned (positive only)

##### Description of `typelength`

Indicates the word length:

- `8` → 8‑bit
- `16` → 16‑bit
- `32` → 32‑bit

##### Description of `typeprecision`

Indicates precision for fixed point types.

The general rule is:

- a leading small letter among `p`, `d`, `r`
  - `p` → negative power of two
  - `d` → negative power of ten
  - `r` → negative power of two times π
- followed by the exponent (without minus sign)

Examples:

- `p7` → precision of 2⁻⁷ (scaling factor 2⁷)
- `p14` → precision of 2⁻¹⁴ (scaling factor 2¹⁴)
- `d1` → precision of 10⁻¹ (scaling factor 10¹)
- `r6` → precision of π·2⁻⁶ (scaling factor 2⁶/π)

Special case:

- precision equal to 1 → `n0`

##### Description of `typebias`

Indicates biasing:

- `b0` → unbiased
- `b1` → biased

Biasing is a technique to save memory by shifting the numeric scale to fit the typical domain.

Example:  
temperature range [-40, 190] °C with precision 1°C can be coded as `u8n0`, then biased by 50 → scale becomes [-50, 205] instead of [0,255].

#### Examples

- **Mechanical torque in [Nm]**, signed, unbiassed, 16‑bit, precision 0.01 [Nm]:  
  `tqMechTrq_s16d2b0`

- **Permanent magnet temperature** range [-20,150] °C, unsigned, biased by -50 °C, 8‑bit, precision 1 °C:  
  `tcMgntTemp_u8n0b1`

- **Phase resistance parameter in [Ohm]**, unsigned, unbiassed, 16‑bit, precision 2⁻²⁰ [Ohm]:  
  `parPhsRsnt_u16p20b0`

- **Conversion constant [rpm]→[rad/s]**, unsigned, unbiassed, 16‑bit, precision 2⁻¹⁹:  
  `cstRpmToRdps_u16p19b0`

---

### Library blocks

Signals, parameters and constants of Simulink **library blocks** follow a specific convention because they may not have predefined physical meaning or data type.

Full name:

`lb_<type><VariableName>`

where `lb` indicates ownership by a library block.

---

### Tables (ASW)

#### Table 1 — List of types for signals, parameters and constants

| Prefix | Physical variable name | Units |
|---|---|---|
| aa | angular acceleration | rad/s² |
| ac | angular position | – |
| ad | angular position | deg |
| ar | angular position | rad |
| bol | boolean | – |
| cst | generic constant | – |
| gen | generic signal | – |
| i | electric current | A |
| ls | electric inductance | H |
| mf | magnetic flux | Vs |
| n | angular speed | rpm |
| par | generic parameter | – |
| pp | pressure | Pa |
| pw | power | W |
| rs | electric resistance | Ohm |
| t | time | s |
| tc | temperature | °C |
| tq | torque | Nm |
| vt | voltage | V |
| w | angular speed | rad/s |

#### Table 2 — List of keywords (ASW)

| Keyword | Full name | Keyword | Full name |
|---|---|---|---|
| Acos | Arccosine | Act | Actual |
| Actn | Action | Actv | Active |
| Alin | Align | Alph | Alpha |
| Amb | Ambient | Amp | Amplitude |
| Ang | Angle, Angular | Atan | Arctangent |
| Asin | Arcsine | Asym | Asymmetric |
| Avg | Average | Axis | Axis |
| Base | Base | Beta | Beta |
| Calc | Calculation | Cath | Cathetus |
| Cnst | Constant | Coef | Coefficient |
| Comp | Compensator | Cond | Condition |
| Cos | Cosine | Cons | Constant |
| Curr | Current | Cntr | Counter |
| Ctrl | Controller | Cycl | Cycle |
| Damp | Damping | Deg | Degree celsius |
| Delt | Delta | Dely | Delay, Delayed |
| Dir | Direct | Dsbl | Disable |
| Diss | Dissipative | Ddnt | Divident |
| Dvsr | Divisor | Dmgz | Demagnetization |
| Drvt | Derivative | Duty | Duty |
| Dyn | Dynamic | Elct | Electric, Electrical |
| Else | Else | Enbl | Enable |
| Enrg | Energy | Est | Estimation, Estimated |
| Fact | Factor | Filt | Filter, filtered |
| Flag | Flag | Fdbk | Feedback |
| Fdwd | FeedForward | Flux | Flux |
| Fric | Friction | Frme | Frame |
| Fst | First | FW | Field Weakening |
| Gain | Gain | High | High |
| Hypt | Hypotenuse | Indx | Index |
| If | If | Inct | Inactive |
| Indc | Inductance | Init | Initial |
| Inp | Input | Inrt | Inertia |
| Intg | Integral, Integrated | Lim | Limit |
| Low | Low, Lower | Ltd | Limited |
| Max | Maximum | Meas | Measurement, Measured |
| Mech | Mechanical | Mag | Magnet |
| Mgtd | Magnitude | Map | Map, Mapper |
| Min | Minimum | Mod | Modulo |
| Mode | Mode | Mot | Motor |
| MTPA | Maximum Torque Per Ampere | Non | Non |
| Norm | Normalized | Oper | Operation |
| Omod | Overmodulation | Outp | Output |
| Over | Over | Perm | Permanent |
| Pssv | Passive | Phs | Phase |
| Pos | Position | Pred | Prediction, Predicted, Predictive |
| Prop | Proportional | Pwm | Pulse width modulation |
| Pwr | Power | Qdrt | Quadrature |
| Rdps | Radiants per second | Reac | Reaction |
| Ref | Reference | Rsrv | Reserve |
| Rmdr | Remainder | Rot | Rotor |
| Rpm | Revolution per minute | Rset | Reset |
| Rslt | Result | Rstn | Resistance |
| Rtio | Ratio | Obs | Observer |
| Samp | Sampling | Sat | Saturation |
| Shft | Shift | Sin | Sine |
| Slop | Slope | Slow | Slow |
| Snd | Second | Spd | Speed |
| Sqr | Square | Sply | Supply |
| Sts | Status | Stat | Static |
| Std | Standard | Stff | Stiffness |
| Sttr | Stator | Swtc | Switch, Switching |
| Sym | Symmetric | Temp | Temperature |
| Time | Time | Tmpr | Temporary |
| Tmr | Timer | Tors | Torsional |
| Trgt | Target | Trgn | Trigonometric |
| Trig | Trigger | Trq | Torque |
| Un | Un | Und | Under |
| Up | Up, Upper | Val | Value |
| Vect | Vector, Vectorial | Visc | Viscosity, Viscous |
| Volt | Voltage | Wind | Winding |
| XYZ | Three phase signal |  |  |

---

## Simulink blocks

Full block name:

`<type>_<BlockName>_<optional>`

#### Description of `<type>`

Indicates block kind. Types include main models, subsystems, action subsystems, enabled subsystems, variants, referenced models/subsystems, libraries, and Stateflow charts.

**Table 3 — Types for Simulink blocks**

| Type | Block |
|---|---|
| ens | Enabled subsystem |
| ias | If action subsystem |
| lib | Library |
| mdl | Main model |
| rmd | Referenced model |
| rss | Referenced subsystem |
| sas | Switch case action subsystem |
| sfc | Stateflow chart |
| sss | Simple subsystem |
| vrs | Variant subsystem |

#### Description of `<BlockName>`

Merged full words/keywords using **PascalCasing**.

#### Description of `<optional>`

- For main models: sampling time (`10ms`, `500µs`, `1s`, …)
- For library blocks:
  - `0` for original library
  - for instances: incremental number (`1`, `2`, …) or VariableName of first input

---

## BSW — C language

### Files

Full file name:

`<modulename><_optional>`

Applies to both `.h` and `.c` (extension excluded).

#### Description of `<modulename>`

Identifies the module. All files in same module share the same `<modulename>`. It is composed by words/keywords in **PascalCasing**.

If a word appears in Table 2 or Table 5, its keyword must be used.

#### Description of `<_optional>`

Optional role descriptor. If used:

- single word/keyword
- first letter capital, remainder lower case
- keyword substitution rules as above

---

### Variables

Full variable name:

`<scope_><variablename><_datatype>`

#### Description of `<scope_>`

Indicates accessibility region, depending on:

- static storage class usage
- declaration region

Five valid categories are listed in Table 6 with corresponding prefixes.

#### Description of `<variablename>`

Meaning‑specific name; duplicates allowed if other parts differ.

Casing depends on storage class (Table 6):

- **PascalCasing** → static variables
- **camelCasing** → non‑static variables

Keywords substitution follows Table 2 & Table 5.

#### Description of `<_datatype>`

Indicates data type + dynamic behavior.

Structure:

`_<pointerqualifier><pointer><typequalifier><type>`

Exception: void / pointer‑to‑void → N/A.

- `<pointerqualifier>`: `v` volatile pointer, `c` const pointer, `r` restrict pointer, else N/A
- `<pointer>`: `p` if pointer, else N/A
- `<typequalifier>`: `v` volatile, `c` const, else N/A
- `<type>`:
  - `b`, `u8`, `u16`, `u32`, `s8`, `s16`, `s32`
  - N/A for user‑defined types

---

### Functions

Full function name:

`<scope_><functionname><_returntype>`

#### Description of `<scope_>`

Indicates scope + defining file.

Two categories (Table 7):

- Global (extern or hfile‑static)
- Local (cfile‑static)

Global prefix is `<modulename>_`.

#### Description of `<functionname>`

Meaning‑specific, PascalCasing.

Keyword substitution as usual.

#### Description of `<_returntype>`

Structure:

`_<pointer><type>`

Exception: void / pointer‑to‑void → N/A.

- `<pointer>`: `p` if pointer return, else N/A
- `<type>`: same set as variables

---

### Constructs

Full construct name:

`<scope_><constructname>_<constructtype>`

#### Description of `<scope_>`

Two categories (Table 8):

- Global (hfile‑declared) → `<modulename>_`
- Local (cfile‑declared) → N/A

#### Description of `<constructname>`

camelCasing, with usual keyword substitution.

#### Description of `<constructtype>`

Entity kind (Table 9).

---

### Construct fields

Full field name:

`<fieldname><_datatype>`

#### Description of `<fieldname>`

camelCasing, with usual keyword substitution.

#### Description of `<_datatype>`

Same structure and rules as variables:

`_<pointerqualifier><pointer><typequalifier><type>`

---

### Defines and enumerative cases

Full name:

`<scope_><macroname>`

Exception: function‑like macros may follow this or function naming rules.

#### Description of `<scope_>`

Two categories (Table 10):

- Global (hfile‑defined) → `<MODULENAME>_` (capital letters)
- Local (cfile‑defined) → N/A

#### Description of `<macroname>`

SNAKE_CASING, with usual keyword substitution.

---

### Tables (BSW)

#### Table 5 — Keywords for C language

| Keyword | Full word |
|---|---|
| Alv | Alive |
| Appl | Application |
| Buf | Buffer |
| Cfg | Configure, Configuration |
| Clr | Clear |
| Diag | Diagnostic |
| Err | Error |
| Flg | Flag |
| Get | Get |
| If | Interface |
| Man | Manager |
| Mdl | Module |
| Mon | Monitor, Monitoring |
| Rd | Read |
| Run | Run |
| Rx | Receive, Reception |
| Stop | Stop |
| Tst | Test |
| Tx | Transmit, Transmission |
| Sch | Schedule |
| Set | Set |
| Warn | Warning |
| Word | Word |
| Wr | Write |

#### Table 6 — Variable scope categories

| Variable scope category | `<scope_>` | `<variablename>` casing |
|---|---|---|
| Global (extern) | `g_` | camelCasing |
| Global static (file‑static) | N/A | PascalCasing |
| Local | `l_` | camelCasing |
| Local static (function‑static) | `l_` | PascalCasing |
| Function argument | N/A | camelCasing |

#### Table 7 — Function scope categories

| Function scope category | `<scope_>` | `<functionname>` casing |
|---|---|---|
| Global (extern or hfile‑static) | `<modulename>_` | PascalCasing |
| Local (cfile‑static) | N/A | PascalCasing |

#### Table 8 — Construct scope categories

| Construct scope category | `<scope_>` | `<constructname>` casing |
|---|---|---|
| Global (hfile‑declared) | `<modulename>_` | camelCasing |
| Local (cfile‑declared) | N/A | camelCasing |

#### Table 9 — Construct entities

| Construct entity | `<constructtype>` |
|---|---|
| Type definition (typedef) | `t` |
| Struct (struct) | `s` |
| Union (union) | `u` |
| Enumerative (enum) | `e` |

#### Table 10 — Macro scope categories

| Macro scope category | `<scope_>` | `<macroname>` casing |
|---|---|---|
| Global (hfile‑defined) | `<MODULENAME>_` | SNAKE_CASING |
| Local (cfile‑defined) | N/A | SNAKE_CASING |

---
