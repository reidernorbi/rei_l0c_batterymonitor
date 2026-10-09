# rei_l0c_batterymonitor

![ROS 2 Humble](https://img.shields.io/badge/ROS_2-Humble-3498DB?logo=ros)
![C++](https://img.shields.io/badge/Language-C++17-blue?logo=c%2B%2B)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen)
![License](https://img.shields.io/badge/License-Apache--2.0-lightgrey)

ROS 2 Humble alapú akkumulátorfigyelő és vészjelző rendszer, amely egy virtuális járműakkumulátor merülését szimulálja, és kritikus töltöttségi szint esetén vészjelzést generál.

---

## Rendszerarchitektúra

```mermaid
flowchart LR
    A["/battery_node"] -->|"/battery_level<br/>(std_msgs/msg/Float32)"| B["/battery_alarm_node"]
    B -->|"/battery_alarm<br/>(std_msgs/msg/Bool)"| C["Terminál / Rendszer"]