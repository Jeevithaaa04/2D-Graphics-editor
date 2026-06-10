# Prompts & Coordinates Cheatsheet

This document provides step-by-step guides (input prompts) to draw shapes and build composite graphics on the 50x20 canvas in the simplified 2D graphics editor.

---

## Canvas Layout Reference

The coordinate system begins at `(0, 0)` in the **top-left corner**:
* **Width (x-axis)**: `0` to `49` (left to right)
* **Height (y-axis)**: `0` to `19` (top to bottom)

```text
(0,0) ----------------------> x (Width: 0 to 49)
  |
  |
  |
  v
  y (Height: 0 to 19)
```

---

## Drawing Walkthroughs

Here are combinations of shapes you can add to create drawings:

### 1. Cozy House & Roof
Draws a house structure with a rectangular base, a triangular roof, and a door.

| Step | Operation | Inputs | Explanation |
| :--- | :--- | :--- | :--- |
| **1** | Add Rectangle | Choose `1` (Add), then `2` (Rectangle)<br>• Top-Left x: `15`<br>• Top-Left y: `8`<br>• Width: `20`<br>• Height: `10`<br>• Draw character: `*` | Builds the main frame of the house. |
| **2** | Add Triangle | Choose `1` (Add), then `4` (Triangle)<br>• x1: `15`, y1: `8`<br>• x2: `34`, y2: `8`<br>• x3: `24`, y3: `3`<br>• Draw character: `^` | Draws the roof sitting directly on top of the frame. |
| **3** | Add Rectangle | Choose `1` (Add), then `2` (Rectangle)<br>• Top-Left x: `23`<br>• Top-Left y: `13`<br>• Width: `4`<br>• Height: `5`<br>• Draw character: `H` | Renders a door on the floor. |

---

### 2. Concentric Target Board
Draws three concentric circles sharing a single center point.

| Step | Operation | Inputs | Explanation |
| :--- | :--- | :--- | :--- |
| **1** | Add Circle | Choose `1` (Add), then `3` (Circle)<br>• Center x: `25`<br>• Center y: `9`<br>• Radius: `8`<br>• Draw character: `#` | Renders the outer rim. |
| **2** | Add Circle | Choose `1` (Add), then `3` (Circle)<br>• Center x: `25`<br>• Center y: `9`<br>• Radius: `5`<br>• Draw character: `*` | Renders the middle rim. |
| **3** | Add Circle | Choose `1` (Add), then `3` (Circle)<br>• Center x: `25`<br>• Center y: `9`<br>• Radius: `2`<br>• Draw character: `O` | Renders the inner bullseye. |

---

### 3. Smiley Face
Draws a face using a outer circle outline, lines for eyes, and a line for a mouth.

| Step | Operation | Inputs | Explanation |
| :--- | :--- | :--- | :--- |
| **1** | Add Circle | Choose `1` (Add), then `3` (Circle)<br>• Center x: `25`<br>• Center y: `9`<br>• Radius: `8`<br>• Draw character: `*` | The face outline. |
| **2** | Add Line | Choose `1` (Add), then `1` (Line)<br>• x1: `20`, y1: `6`<br>• x2: `21`, y2: `6`<br>• Draw character: `o` | Left eye dot. |
| **3** | Add Line | Choose `1` (Add), then `1` (Line)<br>• x1: `29`, y1: `6`<br>• x2: `30`, y2: `6`<br>• Draw character: `o` | Right eye dot. |
| **4** | Add Line | Choose `1` (Add), then `1` (Line)<br>• x1: `21`, y1: `12`<br>• x2: `29`, y2: `12`<br>• Draw character: `-` | Flat smiling mouth. |
