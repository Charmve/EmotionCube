# -*- coding: utf-8 -*-
import dlib                    
import numpy as np            
import cv2                    
import serial
import RPi.GPIO as GPIO  
import time
from skimage import io
import pygame  # pip install pygame

HPWM = 18   # Horizontal engine
VPWM = 13   # Vertical engine
HVcc = 16   # Digtal Vcc       
VVcc = 19

emotion_labs = { # 6 kinds of hunman's emotion
	0: 'Happy',
	1: 'Surprise',
	2: 'Nature',
	3: 'Angry',
	4: 'Disgusted',
	5: 'Fear',
	6: 'Sad'
}

class face_emotion():   #class
    def setServoAngle(self, servo, angle):
        GPIO.setmode(GPIO.BOARD)
        GPIO.setwarnings(False)
        GPIO.setup(servo, GPIO.OUT)
        GPIO.setup(HVcc,GPIO.OUT)
        GPIO.output(HVcc,GPIO.HIGH)
        pwm = GPIO.PWM(servo, 50)
        pwm.start(8)
        dutyCycle = angle / 18. + 3.
        pwm.ChangeDutyCycle(dutyCycle)
        time.sleep(0.3)
        pwm.stop()
        GPIO.cleanup()
        
    def playMusic(self, filename, loops=0, start=0.0, value=0.5):
        flag = False 
        pygame.mixer.init()  
        pygame.mixer.music.load(filename)
        if pygame.mixer.music.get_busy() == False:
           pygame.mixer.music.play(loops=loops, start=start)
        pygame.mixer.music.set_volume(value)  
        time.sleep(15)
        pygame.mixer.music.stop()  
        ''''
        if pygame.mixer.music.get_busy() == True:
          flag = True
        else:
           if flag:
               pygame.mixer.music.stop()
        #       break
         '''
         
    def __init__(self):
        self.detector = dlib.get_frontal_face_detector()
        self.predictor = dlib.shape_predictor("/home/pi/MyProject/dlib-python-test/dlibtest/models/shape_predictor_68_face_landmarks.dat")
        self.cap = cv2.VideoCapture(0)
        self.cap.set(3, 480)
        self.cnt = 0
        
    def learning_face(self):
        line_brow_x = []
        line_brow_y = []
        x0, y0 = 80, 30
        self.setServoAngle(HPWM, x0)
        self.setServoAngle(VPWM, y0)
        while(self.cap.isOpened()):
            flag, im_rd = self.cap.read()
            k = cv2.waitKey(1)
            img_gray = cv2.cvtColor(im_rd, cv2.COLOR_RGB2GRAY)
            faces = self.detector(img_gray, 0)
            font = cv2.FONT_HERSHEY_SIMPLEX
            if(len(faces)!=0):
                global tim
                tim += 1
                print tim
                for i in range(len(faces)):
                    for k, d in enumerate(faces):
                        cv2.rectangle(im_rd, (d.left(), d.top()), (d.right(), d.bottom()), (0, 0, 255))
                        self.face_width = d.right() - d.left()
                        x = d.right() - d.left() /2 + d.left()
                        y = d.top() - d.bottom() /2 + d.bottom()
                        print(x,y) # 输出脸中心到右上顶点的水平和垂直距离
                        shape = self.predictor(im_rd, d)
                        for i in range(68):
                            cv2.circle(im_rd, (shape.part(i).x, shape.part(i).y), 2, (0, 255, 0), -1, 8)
                            cv2.putText(im_rd, str(i), (shape.part(i).x, shape.part(i).y), cv2.FONT_HERSHEY_SIMPLEX, 0.5,
                                        (255, 255, 255))
                        mouth_width = (shape.part(54).x - shape.part(48).x) / self.face_width 
                        mouth_higth = (shape.part(66).y - shape.part(62).y) / self.face_width 
                        print("嘴巴宽度与识别框宽度之比：",mouth_width_arv)
                        print("嘴巴高度与识别框高度之比：",mouth_higth_arv)
                        brow_sum = 0  # 高度之和
                        frown_sum = 0  # 两边眉毛距离之和
                        for j in range(17, 21):
                            brow_sum += (shape.part(j).y - d.top()) + (shape.part(j + 5).y - d.top())
                            frown_sum += shape.part(j + 5).x - shape.part(j).x
                            line_brow_x.append(shape.part(j).x)
                            line_brow_y.append(shape.part(j).y)
                        tempx = np.array(line_brow_x)
                        tempy = np.array(line_brow_y)
                        z1 = np.polyfit(tempx, tempy, 1)  
                        self.brow_k = -round(z1[0], 3)  
                        brow_hight = (brow_sum / 10) / self.face_width  
                        brow_width = (frown_sum / 5) / self.face_width 
                        print("眉毛高度与识别框高度之比：",round(brow_arv/self.face_width,3))
                        print("眉毛间距与识别框高度之比：",round(frown_arv/self.face_width,3))
                        eye_sum = (shape.part(41).y - shape.part(37).y + shape.part(40).y - shape.part(38).y +shape.part(47).y - shape.part(43).y + shape.part(46).y - shape.part(44).y)
                        eye_hight = (eye_sum / 4) / self.face_width
                        if (mouth_higth >= 0.03):  # 0.03
                            if eye_hight >= 0.056:
                                if(tim % INTERVAL == 0):
                                    # tim = 0
                                    ser.write(b'A')
                                    print('Amazing')
                                    self.playMusic('/home/pi/Music/Richard Clayderman - Marry in Dream.mp3')
                                cv2.putText(im_rd, "amazing", (d.left(), d.bottom() + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 2, 4)
                            else:
                                if(tim % INTERVAL == 0):
                                    ser.write(b'H')
                                    print('Happy')
                                    self.playMusic('/home/pi/Music/Charice - Louder.mp3')
                                cv2.putText(im_rd, "happy", (d.left(), d.bottom() + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 2, 4)
                        else:
                            if self.brow_k <= -0.3:
                                if(tim % INTERVAL == 0):
                                    # tim = 0
                                    ser.write(b'G')
                                    print('anGry')
                                    self.playMusic('/home/pi/Music/L3V3LS - On A Hill.mp3')
                                cv2.putText(im_rd, "angry", (d.left(), d.bottom() + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.8,
                                            (0, 0, 255), 2, 4)
                            else:
                                if(tim % INTERVAL == 0):
                                    # tim = 0
                                    ser.write(b'N')
                                    print('Nature')
                                    self.playMusic('/home/pi/Music/Axero - River.mp3')
                                    # time.sleep(10)
                                    # pygame.mixer.music.stop()
                                cv2.putText(im_rd, "nature", (d.left(), d.bottom() + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.8,
                                            (0, 0, 255), 2, 4)
                cv2.putText(im_rd, "Faces: "+str(len(faces)), (20,50), font, 1, (0, 0, 255), 1, cv2.CV_AA)
            else:
                x, y = 80,60 
                cv2.putText(im_rd, "No Face", (20, 50), font, 1, (0, 0, 255), 1, cv2.CV_AA)
            # give some describation
            cv2.putText(im_rd, "S: screenshot", (20, 400), font, 0.8, (0, 0, 255), 1, cv2.CV_AA)
            cv2.putText(im_rd, "Q: quit", (20, 450), font, 0.8, (0, 0, 255), 1, cv2.CV_AA)
            dx = (80 - x) * 0.3125
            dy = -(60 - y) * 0.3125
            print(dx, dy)
            if abs(dx) >= 3:  
                x0 += dx
                print(x0)
                if x0 > 180:  
                    x0 = 180
                elif x0 < 0:
                    x0 = 0
                self.setServoAngle(HPWM, x0) 
            if abs(dy) >= 3:  # 设置阈值
                y0 += dy
                if y0 > 180:
                    y0 = 180
                elif y0 < 0:
                    y0 = 0
                self.setServoAngle(VPWM, y0)  
            # put ’S’ key to cut screen
            if (k == ord('s')):
                self.cnt+=1
                cv2.imwrite("screenshoot"+str(self.cnt)+".jpg", im_rd)
            # put ’Q’ key to exit
            if (k == ord('q')):
                break
            # imshow
            cv2.imshow("camera", im_rd)
            ser.flushInput()
            time.sleep(0.1) # 软件延时
        # release capture
        self.cap.release()
        cv2.destroyAllWindows()
        
if __name__ == "__main__":
    ser = serial.Serial("/dev/ttyS0", 9600) 
    if ser.isOpen == False:
        ser.open()               
    s = ser.write(b"Raspberry pi is ready")
    print ("Wellcom to Emotion Adjustment System\n\n\n")
    INTERVAL = 5 
    tim = 0
    #img=io.imread('/home/pi/MyProject/dlib-python-test/emotiontest/faces/surprise1.jpg')
    # io.imshow(img)
    print ("          MaiweiAI Charmve @Allright Received          ")
    my_face = face_emotion()
    my_face.learning_face()
