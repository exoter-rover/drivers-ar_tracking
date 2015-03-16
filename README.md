Advanced Realtime Tracking system driver
=========================== 
with love from Karl Krespen to Tim and Javi :-*

## Concerns & potential minebombs

### Server and port

This is something that you will have to discover by yourself my little padawans.
- The ART system should be connected to a computer, I have called this computer server_host, we need to know its ip
- There are two ports, one in the server host and another one in the client that we need to know: server_port (might be 50105) and data_port (0 might work, apparently with 0 it is managed by the server_host)

For testing the connection and discovering this three magic numbers I have created test_ArtDriver.cpp inside the ./src/test directory. After a change on it, you should perform amake on the parent folder (~/dev/drivers/ar_tracking). This will generate a binary: ar_tracking/build/test/test_suite.

In order to run it: ./test_suite

I hope Javier likes it and does not show me the middle finger. 

### Reconnection

I doubt that this driver works with reconnections, I haven't taken care about any memory issues or life cycles. If this is a problem we could work on a patch to get it working.

Furthermore, the examples are done (and so is this driver) using a global static object that gets all the data and provides all the methods, for my fellow programmers I would just say that this is like sharing a whore among friends (in times of need is not that bad).


## Types

The software used buy ART system is called DTrack 2 and I had to search for a manual, but I don't have access to that software, so I'm supposing all the time how it works. From what I have read looks pretty similar to Vicon Nexus.

Regarding the type of objects that you can define, my guess is that the most similar to vicon's subjects are DTrack_Body_Type_d, that is one of the many types that you can define (f stands for float, d stands for double):

- DTrack_Marker_Type_f
- DTrack_Marker_Type_d
- DTrack_Body_Type_f
- DTrack_Body_Type_d
- DTrack_Inertial_Type_f
- DTrack_Inertial_Type_d
- DTrack_Flystick_Type_f
- DTrack_Flystick_Type_d
- DTrack_MeaTool_Type_f
- DTrack_MeaTool_Type_d
- DTrack_MeaRef_Type_f
- DTrack_MeaRef_Type_d
- DTrack_Hand_Type_f
- DTrack_Hand_Type_d
- DTrack_Human_Type_f
- DTrack_Human_Type_d

(yes the ART has a lot of cool toys in the documentation, please look at the picture of the flystick and tell me to what it has ressemblances)

Anyway, the before-mentioned test suite should print in the screen everything that the system is seeing so we can get to terms.

For the moment I'm supposing exoter is a DTrack_Body_Type_d

##Rotation matrix

If you see the rover in a weird orientation, means that I didn't understood what "rotation matrix column-wise" was. They serve the rotation matrix in a 1D array of length 9. I have suppossed that the second element of this array is first row-second column 