# -Intelligent-speech-companion-robot-based-on-sentiment-analysis-

Taking emotion analysis and intelligent speech as the research object, in order to improve the current situation of intelligent furniture robot <b>lack of emotional interaction</b>, an intelligent companion robot is designed based on <b>expression recognition</b> and <b>intelligent speech</b>. The system mainly includes an expression recognition camera, an intelligent voice module, and a full color light cube display system. After actual testing, the system has fast response, high recognition accuracy, stable work, and a good experience, making people's lives more intelligent and user-friendly.

- <p><b>Expression Recognition Camera</b>:RasberryPi 3B+, CameraPi </p>
- <p><b>Intelligent Voice Module</b>: intelligent speech based on FPGA, Microphone</p>
- <p><b>Full-color Light-cube Display System</b>: Including power switch circuit, control circuit and cascade drive circuit, and leave enough space to expand subsequent circuits.Especially, this display system come from my another projects: <a href="https://github.com/Charmve/Design-of-a-3D-Dynamic-Display-System-Based-on-Voice-Control" target="_blank">Design-of-a-3D-Dynamic-Display-System-Based-on-Voice-Control</a></p>


![PNG](./02_Pictures/Emotion-Cube.jpg)
<p align="center">Emotion Cube</p>

## Oritation/Application
Function positioning of companion robot:
- <b>Home entertainment</b> The smart speakers equipped with technology terminals such as voice recognition and microphone make the companion robot more humane and improve the happiness of life;
- <b>Popular science education</b> The full-color light cube animation stimulates children's imagination of three-dimensional space, their interest in intelligent technology, and spreads knowledge of three-dimensional modeling;
- <b>Emotional complement</b>
According to the results of sentiment analysis, Light Cube uses different melody music and animations to express their feelings
Love makes interaction more lively and interesting and heals emotions.

## Insights


## How's it going?

<b>1. Dynamic expression recognition</b>

To put it simply, facial expressions are part of the human body's (physical) language, which is a physical and psychological response, usually used to convey emotions. There are many kinds of human facial expressions. At present, the recognition of the six basic human expressions of happiness, surprise, sadness, anger, disgust and fear is relatively good. Facial expressions can be recognized better, and signs and commands are given to control people. The machine interactive device completes the corresponding action. Due to the complexity of human emotions, these expressions are not enough to fully determine the emotional fluctuations in a person's heart. To improve the accuracy of judgment, it is necessary to pass comprehensive evaluations such as heart rate detection and voice processing.

![PNG](./02_Pictures/ExpressionRecognition.jpg)
<p align="center">Figure 1. The effect of facial expression recognition</p>

<b>2. Voice Control Realization</b>

Speech recognition is realized by LDV5 speech module and FPGA speech sampling, filtering and recognition. After a long period of debugging and parameter setting, the recognition rate of commonly used sentences is high, and the voice chat function is completed through local semantic analysis and retrieval. Functions such as intelligent voice answering, light music playback, storytelling, and voice-controlled light cube display are now relatively complete, but the voice recognition rate needs to be improved, and the response time needs to be reduced.

<b>3. Full-color Cube Display</b>

![PNG](./02_Pictures/DynamicDisplay.jpg)
<p align="center"> Figure 2. 3D dynamic display effect diagram of light cube 12*12*12</p>

<b>4. Overall Realization</b>

After the Raspberry Pi is powered on, turn on the camera to perform dynamic expression recognition. When facial expressions are recognized, background music to adjust emotions is played. At the same time, send instructions to STM32 through Bluetooth communication to control the light cube to display different three-dimensional animations, and cooperate with the playing background music to create a relaxed, comfortable and warm home environment, which can effectively relieve people's mental stress and relieve emotions.

![PNG](./02_Pictures/EmotionCube.jpg)
<p align="center"> Figure 3. 3D dynamic display effect diagram of light cube 12*12*12</p>

## How to do it?
<b>1. Overall System Block</b>

As shown in Figure 4, the robot system consists of Raspberry Pi and STM32 as the main controller, and sends the expression recognition result to STM32 to control the light cube to display 3D full-color animation. The Raspberry Pi completes the control of the pan/tilt steering gear so that the camera can track the movement of people; Dlib and Numpy are used for face recognition, facial feature point extraction and algorithm normalization processing to complete facial expression recognition. STM32F4 controls the LED lights of the three-dimensional position of the 12-level full-color light cube to display full-color animation, presenting a 3D picture, and enhancing the visual effect. (Refer to Figure 5 for the specific implementation process)

![PNG](./02_Pictures/SystemBlock.jpg)
<p align="center"> Figure 4. System Block</p>

![PNG](./02_Pictures/ProgramFlowChat.jpg)
<p align="center"> Figure 5.  </p>
  
  
<b>2. Dynamic Expression Recognition</b>
  
First, use dlib to complete face recognition, and extract 68 feature points of face information. Then instantiate a shape_predictor object, use dlib to train face feature detection, and perform face feature point calibration. When calibrating, use the circle method of opencv to add a watermark to the coordinates of the feature point. The content is the serial number and position of the feature point. Next, it is necessary to perform a comprehensive calculation based on the coordinate information of these 68 feature points as a judgment index for each expression.

According to the judgment index we put forward, first calculate the proportion of mouth open. Before selecting the standard value of the indicator, analyze multiple happy face photos and calculate the average of the ratio of open mouth when happy. Use the slope of the fitted straight line to approximate the degree of inclination of the eyebrows. Similarly, calculate the eyebrow height and mouth width of each expression, and then classify and discuss, and give the discrimination threshold. Through the analysis of multiple different expression data, the reference value of each index can be obtained, and simple expression classification standards can be written to complete expression recognition.
  
<b>3. Smart Voice</b>

For audio signal processing, we use the LDV5 module for processing. FPGA simulates SPI to communicate with the module to read the value of its register, and perform FFT fast Fourier transform on it for voice signal processing, and send corresponding instructions through the voice signal. FPGA voice sampling, filtering, and recognition, after a long period of debugging and parameter setting, the recognition rate of commonly used sentences is high, and the voice chat function is completed through local semantic analysis and retrieval.

<b>4. Full-color Light-Cube</b>

Adopt 12 SM16126 serial conversion and strong drive chip cascade to form 144 output port control, input timing control through DateIN data port, carry out PWM modulation, produce RBG color adjustment. Through the host computer of the light cube 3D modeling we designed, we design different animations, mark the 6-bit data of each LED, etc., and finally read each frame of animation of the 12-level light cube in the SD card in DMA mode Realize the full-color animation display of Light Cube.

![PNG](./02_Pictures/Light-Cube.jpeg)

<br>
Go to the .doc/.pdf file in Chinese,click <a href="https://github.com/Charmve/Intelligent-Speech-Sompanion-Robot-Based-on-Sentiment-Analysis/tree/master/02_Docs/" target="_blank">here</a>

<br><br>


* All Rights Reserved ©Charmve
