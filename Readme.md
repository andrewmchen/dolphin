Andrew's Jank Fork of Dolphin
============================

Additional Features
- Pixel Dumping

Pixel Dumping
--------------
Small hack that creates a shared memory buffer to dump pixel output onto. Uses POSIX shm_open so this probably won't work on Windows. Currently hooks into Renderers, DumpFrame function. It's used to dump screenshots and videos so I figured why the hell not. The corresponding python script is in SSAI repo.

![woooo](http://i.imgur.com/t7TLzOx.png)
