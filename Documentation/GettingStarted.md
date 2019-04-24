# Getting Started

## Users

Download the precompiled Windows 10 program from the link below.

[Download Program](https://1drv.ms/f/s!Agd2rQRMWbLZvA8sq7ofLVoG7Ut4)

Extract the zip folder and double click on the `START.bat` file to start the program. If everything goes right the default browser opens and will display the BitBrain Web App.

Enter your first name in the dialog window that pops up and close it by clicking the blue cross. You may now upload an image by click the camera button in the top-left corner. An image called `Example Image.jpg` is provided for testing purposes.

## Programmers

### Prerequisites

Download and install the following programs:

- [Visual Studio](https://visualstudio.microsoft.com/downloads/)
- [Node.js](https://nodejs.org/en/download/)

### Project Setup

- Download the GitHub project.

- Download the [BitBrain Resources](https://1drv.ms/f/s!Agd2rQRMWbLZvA6Nxk2b4NoNTNsV). Place the extracted `Resource` folder in the `BitBrain/Resource` folder. This is the same folder as the `Source` and `Examples` folder.

- Create a folder called `temp` in the `WebApp` folder.

- Install the Node.js modules by opening a terminal in the `WebApp` folder and executing the `npm install` command.

- Open the Visual Studio solution file `BitBrain.sln` and compile the C++ program in x64 Release mode. This is the build configuration the Node.js app references.

- Start the Web App by opening a terminal in the `WebApp` folder and executing the `node app.js` command.

### Documentation

- Examples can be found in the [Examples](https://github.com/laurooyen/BitBrain/tree/master/BitBrain/Examples) folder. The code of these files can be copied to `Main.cpp` to compile them.

- Make sure to read the [ProgramFlow](https://github.com/laurooyen/BitBrain/blob/master/Documentation/ProgramFlow.md) manual to get a better understanding of how everything works.