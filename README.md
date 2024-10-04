# Ghost Prototypes

## First Prototype / Transform & Time Stamp

Record All player states and pass it to a ghost,
ghost play all record information to imitates player actions

### overview
$\color{green)}{\textsf{whats + :}}$

$\color{green)}{\textsf{ - fidelity of movement whith hight register rate}}$

$\color{green)}{\textsf{- simple}}$

$\color{green)}{\textsf{- easy to set up and use}}$

$\color{green)}{\textsf{- good lag resistance}}$

$\color{red}{\textsf{whats - :}}$

$\color{red}{\textsf{- a lot of data register and play}}$

$\color{red}{\textsf{- need hight rate to seem natural movement}}$



 > [!NOTE]
 > can be use for small level, 
 > for wider levels, too many data will be register, and can cause latency



![GhostProto - Unreal Editor 2024-09-25 11-47-28](https://github.com/user-attachments/assets/b6422097-11f2-4d2c-844c-b34a499b7a24)

##Second Prototype / Inputs

Record Player input, and pass it to ghost.
ghost read input fill, and retribut it.

###overview

$\color{green)}{\textsf{whats + :}}$

$\color{green)}{\textsf{ - fidelity of movement}}$

$\color{green)}{\textsf{- standalone, no more informations needed}}$

$\color{green)}{\textsf{- easy use}}$

$\color{red}{\textsf{whats - :}}$

$\color{red)}{\textsf{- lag can mess up with it}}$

$\color{red}{\textsf{- need same configuration to play (placement,speed...}}$



>[!NOTE]
>really efficient in versus game, in replay mode
>can be down with delegate recording, but here it's down to be serielized in JSon file

![GhostProto - Unreal Editor 2024-10-04 14-37-04 (online-video-cutter com)](https://github.com/user-attachments/assets/88e0d73b-3e59-4861-9436-d6a71067505b)





