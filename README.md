# Philosophers

## 🧠 Overview

**Philosophers** is a concurrency project from the 42 curriculum that simulates the classic *Dining Philosophers* problem. The challenge involves creating a program where multiple philosophers alternately eat, think, and sleep without causing race conditions or deadlocks, using **threads** and **mutexes** in C.

This project is designed to deepen your understanding of **thread management**, **mutex synchronization**, and the classic problems of **concurrency** in programming.

## 📌 Mandatory Objectives

- Each philosopher is represented by a thread.
- Forks are represented by mutexes.
- Philosophers must:
  - Take forks (mutex lock)
  - Eat for a defined time
  - Sleep
  - Think
- Prevent deadlocks and data races.
- A monitor thread detects if a philosopher dies (i.e., doesn't eat in time).
- All actions (taking forks, eating, sleeping, dying) are logged with a timestamp and philosopher ID.

## 📦 Usage

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
