This is a basic Arduino code to receive character instructions via bluetooth, and control a Seeed Motor Shield to move in directions based on single character commands received.

The method of steering used here is three part: 

1) Throttle to each motor is controlled by default values. That way, the platform can move in fixed intervals. Also, should one motor be used for steering, or one motor in a skid steering arrangement mechanically turns faster, they can be adjusted as needed and appropriate.

2) 'Steering' is a constant that is assumed to be either in Left, Center, or Right current status. A forward command sent when the last directional command was Center, for example, would cause the platform to move straight forward. If directional command had been Left, it would have moved forward but with a Left drift, Right the opposite, and Back L/C/R operating the same.

3) Instead of simply turning on its axis (which on uneven terrain would not result in fixed increments in rotation) skid steering can still be used, except it will simply drift L, R, or Center in either forward or backward commands.