# Program Flow

This document tries to give an overview of the most important steps BitBrain executes in order to recognize handwritten digits and mathematical symbols.

There are two major parts. The first one is a web application that runs on a Node.js server. This part of BitBrain is responsible for providing a cross platform user interface. The second part is a C++ program that is responsible for performing heavy operations like image processing or calculating the output of neural networks.

Below is a detailed overview of the most important steps. The programming languages or technologies are listed in brackets next to the subheadings. The most important implementation files are listed immediately below it.

## Web Application (HTML, CSS, JS)

Files [[main.ejs](WebApp/views/main.ejs) - [main.js](WebApp/public/js/main.js)]

The web application is responsible for sending an image to the server. For non-programmers to be able to use our program, it was crucial that we had a simple user interface. By writing this with web technologies such as HTML and CSS we could easily run it on desktop and mobile devices.

The following steps are performed by the web application:

- Renders the user interface. There are only two buttons, one to select the image to be processed and one to change some basic settings.

- Sends the selected image to the server. By using the capture attribute of the HTML input element we made sure the default camera app would open on mobile devices.

- Gets the response from the server and renders the bounding boxes, classification results and formula result onto the original image.

On completion, the user can select a new image.

## Server (JS - Node.js)

Files [[app.js](WebApp/app.js)]

The server is responsible for the communication between the web application and the C++ program. We could have embed a WebSocket server in the C++ program, but even then we would still need a webserver to serve the web application itself to our clients. This made the choice for Node.js rather obvious.

The followings steps are performed by the server:

- Waits for a client to send an image.

- Saves the received image to a file. The filename consists of the username and a timestamp in the format 'username-YYYYMMDD-hhmmss'. For optimal performance, the file format of the image doesn't get converted.

- Runs the C++ program using nodes child_process module. This step will extract the classifications and bounding boxes for the symbols in the image. Its results get printed in the form of a JSON object to stdout.

- Sends the data obtained from the C++ program back to the client.

On completion, the server processes the next image in queue. If there is none, it waits until a user sends one.

## Symbol Extractor (C++)

Files [[SymbolExtractor.h](BitBrain/Source/ImageProcessing/SymbolExtractor.h) - [SymbolExtractor.cpp](BitBrain/Source/ImageProcessing/SymbolExtractor.cpp)]

The symbol extractor is responsible for extracting the individual symbols (digits or math operators) out of an image with multiple symbols. Technically speaking we could have done this with artificial intelligence as well but this would have complicated things a lot. Instead we opted for a more classic approach using image processing. Whilst not perfect, it offered a good balance between development time and accuracy.

The following steps are performed by the Symbol Extractor class:

- Converts the input image to a binary image using an adaptive thresholding algorithm. This makes the image processing in the following steps easier.

- Calculates the bounding boxes of individual symbols using connected-component labeling and a breadth first search algorithm to build the required linked lists.

- Removes bounding boxes that are smaller than a certain threshold and thus don't contain any symbols. These small bounding boxes can appear due to an inaccurate threshold in the first step.

- Sorts the bounding boxes based on ascending x and y coordinates. This is necessary because the breadth first search algorithm doesn't detect the bounding boxes in the order we want.

- Copies the pixels of every bounding box to a separate image.

- Scales every image to fit into a 22x22 box and copies the result into a 28x28 image. This is done so that the images have the same size as the images the neural network was trained with.

- Inverts every image such that foreground pixels are white and background pixels are black. This is done so that the images have the same color as the images the neural network was trained with.

On completion, the individual images are passed one by one to the network class.

## Network (C++)

Files [[Network.h](BitBrain/Source/AI/Network.h) - [Network.cpp](BitBrain/Source/AI/Network.cpp)]

The network is responsible for classifying images of a single symbol. It does this using artificial intelligence and more specifically a neural network that is build out of fully connected layers. At startup, the weight matrices and bias vectors of a pre-trained network get loaded. This allows for quick feed-forwards of images trough the network and makes sure users don't have to wait to get the classification results for their images.

The following steps are performed by the Network class:

- Classifies individual images of symbols.

On completion, a JSON object with the bounding boxes extracted by the Symbol Extractor class and the classification results from the Network class gets printed to stdout.
