# Brookie_Skills — Autonomous Robot Control (VEX 2053X)

Autonomous control software for a competition robotics robot (VEX team 2053X, Push Back season). This is the **skills-challenge routine**: a fully autonomous ~60-second run where the robot navigates a field and scores points with no human input — using odometry-based position tracking, PID motion control, and real-time sensor feedback.

The routine here is part of the program that earned **2053X a top-150 global ranking (#138 of 6,818 teams)** in the Robot Skills Challenge.

> **What this is, for non-robotics readers:** an embedded C++ control system that drives a robot along a planned path using closed-loop feedback. It tracks its own position on the field in real time, corrects its motion with PID controllers, and reacts to sensor input (distance, optical/color) to stay accurate over a long autonomous sequence — the same control-systems ideas used in self-driving and industrial robotics, at small scale.

## Technical highlights

- **Odometry position tracking** — the robot continuously estimates its (x, y, heading) on the field from tracking-wheel and IMU data, so movements are specified as *"drive to point (48, -28)"* rather than blind timed motions.
- **PID motion control** — separate tuned PID controllers for driving, turning, heading correction, and swing turns, each with its own gains and exit conditions (settle error, settle time, timeout).
- **Boomerang / pose-based movement** — `drive_to_pose()`-style motion that arrives at a target position *and* a target heading simultaneously, using a lead-based curved path.
- **Sensor-based position resets** — distance sensors re-localize the robot against field walls mid-routine (`horizontalResetPosition()` / `rightHorizontalResetPosition()`), correcting the odometry drift that accumulates over a long run. This is the key trick for keeping a 60-second autonomous accurate.
- **Concurrent tasks** — color sorting (optical + distance sensor), anti-jam intake logic, and controller feedback run as parallel tasks alongside the main routine.
- **Quadrant / heading state tracking** — helper logic (`updateQuadrant()`, `updateHeading()`) maintains awareness of field region and facing direction for decision-making.

## How it's organized

```
src/
├── main.cpp            Entry point, competition setup, driver/auton selection
├── autons.cpp          The autonomous routines (skills run + test routines)
├── motion.cpp          Custom motion layer — pose movement, position resets, field state
├── tasks.cpp           Concurrent tasks — color sort, anti-jam, controller feedback
├── functions.cpp       Mechanism helpers (intake, scoring, hooks, matchloader)
├── robot-config.cpp    Motor / sensor / device configuration
└── JAR-Template/       Underlying drive library (PID, odometry, drive primitives)
    ├── PID.cpp
    ├── odom.cpp
    ├── drive.cpp
    └── util.cpp
```

Built in **C++** on the VEX V5 platform, extending the open-source [JAR-Template](https://github.com/JacksonAreaRobotics/JAR-Template) odometry library with a custom motion and task layer (`motion.cpp`, `tasks.cpp`) written for this robot.

## What the skills routine does

The main routine (`blue_solo()` in `autons.cpp`) executes a long, tuned sequence: navigate to loading positions, intake game pieces, drive to goals using pose-based movement, score, re-localize against walls with distance sensors, and repeat across the field — all timed and tuned to maximize points within the run's time limit. The commit history (61 commits, e.g. *"3.5 apac lunch tune"*, *"pre-APAC working skills auto full route"*) reflects iterative tuning toward the APAC championship.

## What I learned / took away

- Implementing and **tuning PID controllers** for real hardware — balancing responsiveness against overshoot and oscillation across driving, turning, and swinging.
- **Odometry and its failure mode:** position estimates drift over time, and correcting that with sensor-based re-localization is what makes a long autonomous reliable.
- Structuring a **real-time embedded system** with concurrent tasks that share state safely.
- Iterative, measurement-driven tuning — the difference between code that works once and code that works consistently under competition conditions.

---

*Autonomous control code for VEX team 2053X. Built on the JAR-Template odometry library with a custom motion, task, and sensor-fusion layer.*
