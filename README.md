This repository contains the source code for a turn-based Role-Playing Game (RPG) designed to run in a console environment. It was developed as the final project for the **Object-Oriented Programming (OOP)** course at the Università degli Studi di Cassino e del Lazio Meridionale during the 2021 academic year.

---

## Game Mechanics Overview

The game is structured as a series of sequential **one-on-one turn-based battles**. Defeating an enemy progresses the player to the next floor.

### 1. Character Creation

New characters start with **25 available Skill Points (PA)** to allocate across seven core attributes.

#### S.P.E.C.I.A.L. Attributes (Max Level 10)

| Attribute | Abbreviation | Primary Effect |
| :--- | :--- | :--- |
| **Strength** | STR (S) | Increases Attack Value, resulting in higher damage. |
| **Perception** | PER (P) | Increases the probability of inflicting critical hits. |
| **Endurance** | END (E) | Increases damage reduction and enhances armor defense. |
| **Charisma** | CHA (C) | Boosts the critical damage multiplier and provides a discount at the shop. |
| **Intelligence**| INT (I) | Increases the experience (XP) gained from defeated enemies. |
| **Agility** | AGI (A) | Increases the chance to dodge enemy attacks. |
| **Luck** | LCK (L) | Increases the chance of obtaining dropped items (weapons/armor) and improves hit probability against agile enemies. |

### 2. Combat Actions

During the player's turn, three actions are available:

* **Attack:** Inflicts damage on the enemy.
* **Defend:** Reduces incoming damage from the enemy's next attack significantly, but prevents the player from attacking that turn.
* **Heal:** Uses a potion to restore a percentage of lost health points.

### 3. Equipment and Item Scaling

Weapons and armor provide bonuses to a specific attribute and increase the player's Attack or Defense value.

* **Weapon Scaling:** A key mechanic is "**scaling**". A weapon's effective attack value is incremented based on a specific character attribute (e.g., Perception).
* **Scaling Quality:** The quality of this scaling is determined by a letter grade, from worst to best: **E, D, C, B, A, S**.

### 4. Progression and Persistence

* **Post-Battle:** Defeated enemies grant **Experience Points (XP)** (increasing max HP) and **Gold Coins (G)**. Items may also drop.
* **Shop:** Gold is spent at the shop to purchase permanent upgrades, such as increasing cure potency, increasing the number of cures available, or buying additional Skill Points (PA).
* **Game Over:** Upon reaching 0 HP, the character's level, weapons, and armor are reset. However, **earned Gold and permanent shop upgrades are retained**. The character is automatically saved.
