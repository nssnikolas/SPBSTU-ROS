# SPBSTU-ROS
### 4th grade lab works

---

### Work #1. Option #6. Solving SLAE.

This package solves second-order SLAE. 
The solution is to contact the service with a request of six numbers (coefficients of the equation).
For example, a query with the parameters "5 6 7 1 2 3" I is the following system of equations:
> 5x + 6y = 7
> 
> x + 2y = 3

To start, you need to:
- Clone data from the repository to the src workspace ROS:

For example, if the workspace is: ~/workspace, then the folder ~/workspace/src/ should contain the folder uss_cs

- Assemble a package from the workspace
- Run `roscore` in the first terminal
- Launch the service in the second terminal:

`rosrun uss_cs service`

- In the third terminal, launch the subscriber of the topic to which the service publishes data:

`rosrun uss_cs subscriber`

- And in the last terminal, you can send a request to the service with the command: 

`rosservice call /slae_solver 1 2 3 4 5 6`

Where "1 2 3 4 5 6" are the SLAE coefficients.

---

### Work #2. SLAM

