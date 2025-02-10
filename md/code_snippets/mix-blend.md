---
title: "CSS Mix-Blend-Mode Example"
---

.w {
  position: relative;
  width: 100%;
  background: #fff;
}

.i() {
  width: 10%;
  background: #000;
}

.b {
  position: absolute;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  background: #002fa7;
  mix-blend-mode: screen; 	 /*Cb + (Ci/Cw) - (Cb * (Ci/Cw))*/
  z-index: 2;
}

this will make i's background color to be b's bg-color, and area outside the i will be #fff

