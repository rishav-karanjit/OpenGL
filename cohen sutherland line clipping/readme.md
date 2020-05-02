<b>Algorithm of Cohen Sutherland Line Clipping</b><br>
<b>Input:</b> Two endpoints of a line, Clipping window size(xmin,xmax,ymin,ymax)<br>
<b>Output:</b> Displays what part of the line is clipped and what part of line is not clipped

<b>Step 1:</b> Extend the window to infinity<br>
&emsp;&emsp;&emsp; Break the window into 9 regions<br>

<b>Step 2:</b> Assign each region with unique 4bit binary number b0b1b2b3<br><br>
b0 = 1 if y>ymax<br>
&emsp;&emsp; 0 otherwise

b1 = 1 if y<ymin<br>
&emsp;&emsp; 0 otherwise

b2 = 1 if x>xmax<br>
&emsp;&emsp; 0 otherwise

b3 = 1 if x<xmin<br>
&emsp;&emsp; 0 otherwise <br>

<b>Step 3:</b> For each end points compute its outcodes(rule same as above binary number)<br>

<b>Step 4:</b> Consider a line segment whose outcodes are given by o1 = outcode(x1, y1) and o2 = outcode(x2, y2).
We can now reason on the basis of these outcodes. There are four cases:

<b>Case 1:</b>(o1 = o2 = 0). Both endpoints are inside the clipping window.<br>
<b>Case 2:</b>(o1 = 0, o2 = 0; or vice versa). One endpoint is inside the clipping window;one is outside.<br>
<b>Case 3:</b>(o1 & o2 = 0)Both endpoints are outside but part of line segment falls inside the window. <br>
<b>Case 4:</b>(o1 & o2 = 0)Both endpoints are outside and no part of line segment falls inside the window.<br><br>
<b>Case 1:</b><br><img src="Case1.jpg">
<b>Case 2:</b><br><img src="Case%202.jpg">
<b>Case 3:</b><br><img src="Case%203.jpg">
<b>Case 4:</b><br><img src="case%204.jpg">
