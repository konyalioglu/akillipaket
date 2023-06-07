# akillipaket

This is a ROS2 package to perform heading and position control for a parachute drone. The parachute drone in this project is the autonomous aerial vehicle that carries the payload of the delivery system. To boost its efficiency, it is designed to be a low-cost drone. It has two propulsion system that provides thrust in the x-axis which lies on the vector that propulsive force is generated. With regard to this, a body-fixed axes system is established regarding NED axes. It includes two propellers that enable heading angle control with respect to the Earth-fixed axes system, and landing at a specified spot is possible by adjusting the robot's speed along its x-axis. At the landing spot, it is considered to put an Aruco marker and by using the Aruco marker detection algorithm, it is aimed that estimation of the velocity and position can be performed more accurately. Also, the parachute drone possesses a gyroscope, an accelerometer, a magnetometer, and a GPS module. In order to obtain the orientation of the robot the AHRS algorithm is used. On the other hand, because GPS position measurements are very noisy, a position estimation algorithm is established by using a Kalman Filter. The control of the heading angle is provided by using a cascade PID controller. After settling the heading angle, velocity and position can be controlled using cascade PID as well. 

## Calibration

### Camera Calibration

To calibrate the camera one can run 'cameraCalibration' node,

```
ros2 run calibration cameraCalibration
```

During calibration, a 9x6 chess board will be required. To use chess board with different size, one can change the line given as follows

https://github.com/konyalioglu/akillipaket/blob/ed3229e4b82e65f000ef5bb587e6bae1579189b8/calibration/cameraCalibration.py#L49

### Gyro Calibration

For gyroscope calibration, the 'gyroCalibration' node should be launched;

```
ros2 run calibration gyroCalibration
```

The gyro should be stayed still during calibration process.

### Magnetometer Calibration

For magnetometer calibration, the 'magnetometerCalibration' node should be launched;

```
ros2 run calibration magnetometerCalibration
```

Hold the vehicle in the air and rotate it so that each side (front, back, left, right, top and bottom) points down towards the earth for a few seconds in turn. Consider a full 360-degree turn with each turn pointing a different direction of the vehicle to the ground. 

Do not calibrate the compasses near any metallic or magnetic field producing object (computers, cell phones, metal desks, power supplies, etc.) or incorrect calibration will occur.

### Level Calibration

To obtain the roll and pitch angle offset values, level calibration should be performed as follows:

```
ros2 run calibration levelCalibration
```

During the calibration process, the sensor should be still.

## Running the package


## Drivers
- MPU6050 Driver - I2Cdev library collection - MPU6050 I2C device class by Jeff Rowberg <jeff@rowberg.net>

## References
- https://docs.opencv.org/4.x/dc/dbb/tutorial_py_calibration.html
