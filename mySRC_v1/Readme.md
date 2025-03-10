# Setting Up Arduino-CLI with VS Code

## 1. Install Arduino-CLI
Follow the installation instructions in the [Arduino-CLI Github](https://github.com/arduino/arduino-cli?tab=readme-ov-file) to install Arduino-CLI.

---

## 2. Connect the Board and Install the Core
Refer to the [Getting Started guide](https://arduino.github.io/arduino-cli/1.1/getting-started/#connect-the-board-to-your-pc):

1. Connect your Arduino board to your PC.
2. Install the core for your board.

> **Note:** If your board is identified as "Unknown," the core is likely `arduino:avr`.

---

## 3. Install VS Code
Download and install Visual Studio Code from the [official website](https://code.visualstudio.com/download).

---

## 4. Install Arduino Extension for VS Code
In VS Code:

1. Open the Extensions Marketplace.
2. Search for and install **"Arduino Community Edition"**.
3. Go to the Settings of the **"Arduino Community Edition"**.
4. Set the **"Arduino: Path"** where you installed the arduino-cli.
5. Check the box on **"Arduino: Use Arduino Cli"**
---

## 5. Configure Your Arduino Project in VS Code

1. Open the folder containing your Arduino code in VS Code.
2. Click **"Select Serial Port"** at the bottom of the VS Code window and choose the serial port for your Arduino board.
3. A `.vscode` folder with an `arduino.json` file will be created. Edit `arduino.json` as follows:

```json
{
    "sketch": "your_sketch_file.ino",
    "port": "/your_arduino_port",
    "board": "arduino:avr:uno",
    "output": "../build",
    "intelliSenseGen": "global"
}
```

> Replace `your_sketch_file.ino` and `/your_arduino_port` with the appropriate values for your project.

---

## 6. Install Required Libraries

1. Press `Ctrl+Shift+P` in VS Code.
2. Select **"Arduino: Library Manager"** from the Command Palette.
3. Install the libraries specified in your `requirements.txt` file.

---

## Troubleshooting
1. If you have compile errors related to "std::nothrow", follow this [link](https://github.com/mike-matera/ArduinoSTL/issues/84#issuecomment-1337008712)

You are now ready to use Arduino-CLI with VS Code!
