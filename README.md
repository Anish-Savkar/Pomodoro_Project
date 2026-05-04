# C++ Pomodoro Timer

A feature-rich C++ command-line Pomodoro timer with customizable sessions, sound notifications, daily logging, progress tracking, pause/resume functionality, and weekly summaries, built using a modular and scalable file-based architecture.

---

## ✨ Features

- Customizable study, break sessions, and cycles  
- Sound notifications for session transitions  
- Pause and resume functionality  
- Daily session logging  
- Tracks total sessions, duration, tasks, and breaks  
- Weekly summary and analytics  
- Daily goal tracking with progress bar  
- Modular and scalable file-based data system  

---

## 📸 Feature Previews

### Customized Session Cycle

<img width="766" height="834" alt="Customized session cycle interface" src="https://github.com/user-attachments/assets/e7e54f21-ba2d-4b47-847d-149aa3110ba7" />

Enables full control over session parameters including study time, break duration, cycle count, and loop settings for flexible productivity management.

---

### Session Logging

<img width="643" height="814" alt="Session logging output" src="https://github.com/user-attachments/assets/cf31dc30-c0a3-4e3e-a81a-6719fbf78e7a" />

Displays stored session data including completed sessions, study duration, break time, and task tracking for each day.

---

### Daily Goal and Progress Visualisation

<img width="1047" height="237" alt="Daily progress bar" src="https://github.com/user-attachments/assets/64c67ffb-2f68-4afb-a95c-e78d0255cd7b" />

Shows daily goal tracking with a progress bar that updates dynamically based on completed sessions.

---

### Weekly Statistics

<img width="1067" height="662" alt="Weekly statistics output" src="https://github.com/user-attachments/assets/9dcf011f-64a2-4fc6-85a8-5cd78e9afa5e" />

Displays a summary of sessions, total study time, and break durations over the week.

---

## 🛠️ How to Run

### Compile
```bash
g++ main.cpp pomodoro.cpp -o pomodoro -lwinmm
