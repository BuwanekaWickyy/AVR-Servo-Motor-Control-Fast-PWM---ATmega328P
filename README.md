#  AVR Servo Motor Control (Fast PWM)

A minimalist embedded C project to control a standard hobby servo motor using the AVR ATmega328P microcontroller. The project utilizes Timer/Counter1 in **Fast PWM mode** with **ICR1 as TOP** to generate the required control signal.

##  Features

* **Servo Control:** Drives a servo motor by generating a control pulse ranging from 1ms to 2ms.
* **Fixed Frequency PWM:** Uses Timer/Counter1 to maintain a precise **50 Hz** (20ms period) PWM frequency.
* **Motor Sweep:** Loops through the full range of the servo (1ms to 2ms pulse width) to sweep its angle.
* **Low-Level C:** All peripheral configuration is done via direct register manipulation (TCCR1A, TCCR1B, ICR1, OCR1A).

## Technical Details

This project leverages the **16-bit Timer/Counter1** on the ATmega328P.

### PWM Configuration

| Register | Value/Bit | Setting | Explanation |
| :--- | :--- | :--- | :--- |
| **F\_CPU** | 16,000,000 Hz | Clock Speed | The microcontroller's operating frequency. |
| **Prescaler** | `_BV(CS11)` | clk/8 | $16,000,000 / 8 = 2,000,000$ counts per second. |
| **Mode** | `_BV(WGM13)` \| `_BV(WGM12)` \| `_BV(WGM11)` | Fast PWM, TOP = ICR1 | Mode 14. Provides a fixed frequency defined by ICR1. |
| **Frequency (ICR1)** | `ICR1 = 4000` | 50 Hz | $\text{Frequency} = \frac{\text{F\_CPU}}{\text{Prescaler} \times (\text{TOP} + 1)} = \frac{16,000,000}{8 \times 4000} = 500 \text{ Hz}$ |
| **Output** | `_BV(COM1A1)` | Non-Inverting | Clear OC1A on Compare Match, Set at TOP. |

### Pulse Width Calculation

The servo control signal requires a pulse width between 1ms (minimum angle) and 2ms (maximum angle).

| Pulse Width | Compare Value (OCR1A) | Calculation | Servo Angle |
| :--- | :--- | :--- | :--- |
| **1 ms** | 2000 | $1 \text{ ms} \times 2,000,000 \text{ counts/s}$ | $\approx 0^\circ$ |
| **2 ms** | 4000 | $2 \text{ ms} \times 2,000,000 \text{ counts/s}$ | $\approx 180^\circ$ |

The main loop iterates `OCR1A` from **2000 to 4000** to sweep the servo's full range.

##  Hardware Connections

| AVR Pin (ATmega328P) | Purpose |
| :--- | :--- |
| **PB1 (OC1A/D9)** | PWM Output to Servo Signal Pin |
| **PD4** | Direction Output (Not used for servo, likely leftover from another project) |
| **PD5** | Direction Output (Not used for servo, likely leftover from another project) |

***Note:*** *The output for $\text{OC1A}$ (connected to $\text{PB1}$ or Arduino $\text{D9}$) is where the servo signal wire should be connected. The $\text{PD4}$ and $\text{PD5}$ lines in the code are set as outputs but do not affect the servo control.*

##  Dependencies

* AVR-GCC Toolchain
* `avr-libc`
* Any standard AVR programmer (e.g., USBasp) and `avrdude` for flashing.
