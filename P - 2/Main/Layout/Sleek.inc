[Variables]
H=(#Height#*#scale#)
VolumeW=(220*#scale#)
MediaW=(350*#Scale#)
LocksW=(220*#scale#)
P=(20*#Scale#)

MHC_Reset=[!SetOption MediaHoverCircle Fill "Fill Color #FontColor#,20"][!UpdateMeter MediaHoverCircle][!Redraw]

mVolume.Class=Audio level
mBrightness.Class=Brightness level
mVolume.Class.Description=%1
mBrightness.Class.Description=Changing brightness

[CircleSliderCenterX]
Measure=Calc
Formula=(#VolumeW#/2)
[CircleSliderCenterY]
Measure=Calc
Formula=(#H#-#P#*2-((#VolumeW#-#P#*4)/2))

[CircleSliderRadius]
Measure=Calc
Formula=((#VolumeW#-#P#*4)/2)
OnUpdateAction=[!CommandMeasure Func "ImportCircleSlider()"]

[Sec.BottomButton:S]
X=(#P#)R
Y=r
W=(20*#scale#)
H=(20*#scale#)
Grayscale=1
ImageTint=#FontColor#
DynamicVariables=1
Group=Music | Standard
Container=MediaC
MouseOverAction=[!SetOption MediaHoverCircle X "([#CURRENTSECTION#:X]-#VolumeW#)"][!SetOption MediaHoverCircle Y "([#CURRENTSECTION#:Y])"][!ShowMeter MediaHoverCircle][!UpdateMeter MediaHoverCircle][!Redraw]
MouseLeaveAction=[!HideMeter MediaHoverCircle][!Redraw]
LeftMouseDownAction=[!SetOption MediaHoverCircle Fill "Fill Color #FontColor#,150"][!UpdateMeter MediaHoverCircle][!Redraw]

; ---------------------------------------------------------------------------- ;
;                                   Function                                   ;
; ---------------------------------------------------------------------------- ;


[mVolume]
OnChangeAction=[!CommandMeasure Func "DrawCircleSlider([mVolume:])"]
[mBrightness]
OnChangeAction=[!CommandMeasure Func "DrawCircleSlider([mBrightness:])"]


[VolumeMouse]
Measure=Plugin
Plugin=Mouse
RelativeToSkin=1
RequireDragging=1
DynamicVariables=1
LeftMouseDragAction=[!CommandMeasure Func "CalcCircleSliderPercentage($MouseX$,$MouseY$)"]
LeftMouseUpAction=[!CommandMeasure VolumeMouse "Stop"]


[FrostedGlass]
Measure=Plugin
Plugin=FrostedGlass
Type=#Blur#
Corner=#BlurCorner#
Border=None


; --------------------------------- VolumeBar -------------------------------- ;

[VolumeB]
Meter=Shape
X=1
Y=1
Shape=Rectangle 0,0,#VolumeW#,#H#,#R# | StrokeWidth #Stroke# | Fill Color #PrimaryColor#,#PrimaryOpacity#
Group=Standard
MouseScrollUpAction=[!CommandMeasure "mVolume" "ChangeVolume 2"][!UpdateMeasure mVolume]
MouseScrollDownAction=[!CommandMeasure "mVolume" "ChangeVolume -2"][!UpdateMeasure mVolume]
[VolumeC]
Meter=Shape
X=r
Y=r
Shape=Rectangle 0,0,#VolumeW#,#H#,#R# | StrokeWidth 0 | Fill Color 255,255,255,(255*#TweenNode1#)
Group=Standard | Animated
DynamicVariables=1

[VolumedDeviceTitleString]
Meter=String
MeterStyle=String:S
X=(#VolumeW#/2)
Y=(#P#)
W=(#VolumeW#-#P#/2)
ClipString=1
StringAlign=Center
FontWeight=650
FontSize=(16*#scale#)
Text=[##CurrentSlider#.Class]
DynamicVariables=1
Group=Dynamic | Standard
Container=VolumeC

[VolumedDeviceString]
Meter=String
MeterStyle=String:S
X=r
Y=R
W=(#VolumeW#-#P#/2)
ClipString=1
FontColor=#FontColor2#
StringAlign=Center
MeasureName=#CurrentSlider#
Text=[##CurrentSlider#.Class.Description]
DynamicVariables=1
Group=Dynamic | Standard
Container=VolumeC

[PseudoShadow]
Meter=String
MeterStyle=String:S
Text=[\xef4a]
X=(#VolumeW#/2)
y=([CircleSliderCenterY]+14*#scale#)
StringAlign=CenterCenter
Container=VolumeC
FontFace=Material Icons Round
FontSize=(([CircleSliderRadius]*2.3)*#TweenNode1#)
FontColor=#primaryColor#,([#CurrentSlider#:]/100*255)
InlineSetting=Shadow | 0 | 0 | 8 | 187, 221, 238,([#CurrentSlider#:]/100*50)
Group=Dynamic | Standard | Animated
DynamicVariables=1

[VolumeBar]
Meter=shape
Shape=Ellipse (#VolumeW#/2),([CircleSliderCenterY]),([CircleSliderRadius]) | StrokeWidth (4*#scale#) | Fill Color 0,0,0,1 | Stroke Color #FontColor2# | Scale #TweenNode1#,#TweenNode1#
Shape2=Ellipse (#VolumeW#/2),([CircleSliderCenterY]),([CircleSliderRadius]*[#CurrentSlider#:]/100) | StrokeWidth 0 | Fill Color #AccentColor1#,10 | Scale #TweenNode1#,#TweenNode1#
Line=0,0 | LineTo 0,0
Shape3=Path Line
CircleSliderLine=StrokeWidth (10*#scale#) | Stroke LinearGradient AccentGradient | StrokeStartCap Round | StrokeEndCap Round | Fill Color 0,0,0,0 | Scale #TweenNode1#,#TweenNode1#
AccentGradient=45 | #AccentColor1# ; 0 | #AccentColor2# ; 1
LeftMouseDownAction=[!CommandMeasure VolumeMouse "Start"]
Group=Dynamic | Standard | Animated
DynamicVariables=1
Container=VolumeC

[VolumeString]
Meter=String
MeterStyle=String:S
X=(#VolumeW#/2)
Y=([CircleSliderCenterY])
StringAlign=CenterCenter
FontWeight=650
FontSize=(16*#scale#*#TweenNode1#)
Text=[&Func:volumeLevel('Muted', '%')]
DynamicVariables=1
InlineSetting=Shadow | 0 | 0 | 5 | #FontColor#,170
Group=Dynamic | Standard | Animated
Container=VolumeC

; --------------------------------- Media -------------------------------- ;

[MediaB]
Meter=Shape
X=r
Y=r
DynamicVariables=1
Shape=Rectangle 0,0,(#VolumeW#),(#H#),(#R#+1) | StrokeWidth 0 | Fill Color #PrimaryColor#,#PrimaryOpacity#
Shape2=Rectangle 0,0,(#VolumeW#+#MediaW#),(#H#),#R# | StrokeWidth 0
Shape3=Combine Shape | XOR Shape2
; Shape4=Line #P#,#H#,(#H#-#P#),#H#
Group=Music | Standard
[MediaC]
Meter=Shape
X=(#VolumeW#)
Y=r
Shape=Rectangle 0,0,(#MediaW#),(#H#),#R# | StrokeWidth 0 | Fill color 255,255,255,(255*#TweenNode1#)
Group=Music | Standard | Animated
DynamicVariables=1

[MediaImage]
Meter=Image
X=0
Y=0
W=(#MediaW#)
H=(#H#)
PreserveAspectRatio=2
MaskImageName=#@#Images\FadeMask.png
ImageName=[#PlayerType#Cover]
DynamicVariables=1
Group=Music | Standard | MediaImage
Container=MediaC
Greyscale=1

; ---------------------------- Media info section ---------------------------- ;

[MediaProgress]
Meter=String
MeterStyle=String:S
X=#P#
Y=(#H#/2+50*#scale#)
FontSize=(28*#scale#)
Text=[#PlayerType#CurrentPosition]
FontWeight=650
StringAlign=LeftBottom
DynamicVariables=1
UpdateDivider=1
Group=Music | Standard
Container=MediaC

[ProgBar]
Meter=Shape
X=#P#
Y=r
Shape=Line 0,0,((#MediaW#-#P#*2-100*#scale#)*#TweenNode1#),0 | StrokeWidth 2 | Fill Color 0,0,0,1 | Stroke Color #FontColor#,50 | StrokeStartCap #Cap# | StrokeEndCap #Cap#
Shape2=Line 0,0,((#MediaW#-#P#*2-100*#scale#)*[#PlayerType#Progress]/100*#TweenNode1#),0 | StrokeWidth 4 | Fill Color 0,0,0,1 | Stroke LinearGradient This | StrokeStartCap #Cap# | StrokeEndCap #Cap#
This=0 | #AccentCOlor1# ; 0.0 | #AccentColor2# ; 1.0
LeftMouseUpAction=[!SetOption PosCalc Formula "($MouseX$/(#MediaW#-#P#*2-100*#scale#)*100)"][!UpdateMeasure PosCalc]
DynamicVariables=1
UpdateDivider=1
Group=Music | Standard | Animated
Container=MediaC
[PosCalc]
Measure=calc
OnUpdateAction=[!CommandMeasure state#NowPlayingMedia# "SetPosition [PosCalc]"][!UpdateMeasure #PlayerType#Progress]
Disabled=1
DynamicVariables=1
UpdateDivider=-1
Group=NUOL

[MediaLength]
Meter=String
MeterStyle=String:S
X=R
Y=(-5*#scale#)r
Text=[#PlayerType#Length]
FontColor=#FontColor2#
StringAlign=RightBottom
DynamicVariables=1
UpdateDivider=1
Group=Music | Standard
Container=MediaC

[MediaTrack]
Meter=String
MeterStyle=String:S
X=#P#
Y=(20*#scale#)r
W=(#MediaW#-150*#scale#)
FontSize=(16*#scale#)
ClipString=1
Text=[#PlayerType#Track]
DynamicVariables=1
Group=Music | Standard
Container=MediaC
[MediaArtist]
Meter=String
MeterStyle=String:S
X=r
Y=R
W=(#MediaW#-150*#scale#)
FontColor=#FOntCOlor2#
ClipString=1
Text=[#PlayerType#Artist]
DynamicVariables=1
Group=Music | Standard
Container=MediaC

; ----------------------- Media controls right section ----------------------- ;

[MediaControlShape]
Meter=Shape
X=(#MediaW#+#R#/2)
Y=R
Shape=Rectangle 0,0,(-100*#scale#),(-40*#scale#),(#R#/2) | StrokeWidth 0 | Fill Color #FOntColor#,50
Container=MediaC

[MediaPlayPause]
Meter=Image
X=((-100+100/2-(40+#P#/#scale#)/2)*#scale#)r
Y=(-30*#scale#)r
MeterStyle=Sec.BottomButton:S
[Play]
ImageName=#@#Icons\Play.png
LeftMouseUpAction=[!SetOption MediaPlayPause MeterStyle "Sec.BottomButton:S | Pause"][!UpdateMeter MediaPlayPause]#MHC_Reset#[!CommandMeasure state#NowPlayingMedia# "PlayPause"]
[Pause]
ImageName=#@#Icons\Pause.png
LeftMouseUpAction=[!SetOption MediaPlayPause MeterStyle "Sec.BottomButton:S | Play"][!UpdateMeter MediaPlayPause]#MHC_Reset#[!CommandMeasure state#NowPlayingMedia# "PlayPause"]
[MediaNext]
Meter=Image
ImageName=#@#Icons\Next.png
LeftMouseUpAction=[!CommandMeasure state#NowPlayingMedia# "Next"]#MHC_Reset#
MeterStyle=Sec.BottomButton:S

; -------------------------------- Top buttons ------------------------------- ;

[MediaShuffle]
Meter=Image
X=(#MediaW#-20*#scale#-#p#)
Y=#P#
ImageName=#@#Icons\Shuffle.png
MeterStyle=Sec.BottomButton:S
[Shuffle0]
ImageAlpha=150
LeftMouseUpAction=[!SetOption MediaShuffle MeterStyle "Sec.BottomButton:S | Shuffle1"][!UpdateMeter MediaShuffle]#MHC_Reset#[!CommandMeasure state#NowPlayingMedia# "Shuffle"]
[Shuffle1]
ImageAlpha=255
LeftMouseUpAction=[!SetOption MediaShuffle MeterStyle "Sec.BottomButton:S | Shuffle0"][!UpdateMeter MediaShuffle]#MHC_Reset#[!CommandMeasure state#NowPlayingMedia# "Shuffle"]

[MediaRepeat]
Meter=Image
X=(-#P#-20*#scale#)r
Y=r
MeterStyle=Sec.BottomButton:S
LeftMouseUpAction=[!CommandMeasure state#NowPlayingMedia# "Repeat"]#MHC_Reset#
[Repeat0]
ImageAlpha=150
ImageName=#@#Icons\Repeat.png
[Repeat1]
ImageName=#@#Icons\Repeat.png
[Repeat2]
ImageName=#@#Icons\RepeatOne.png

[MediaHeart]
Meter=Image
X=(-#P#-20*#scale#)r
Y=r
MeterStyle=Sec.BottomButton:S
[FullHeart]
ImageName=#@#Icons\HeartFull.png
LeftMouseUpAction=[!SetOption #CURRENTSECTION# MeterStyle "Sec.BottomButton:S | EmptyHeart"][!UpdateMeter #CURRENTSECTION#]#MHC_Reset#[!CommandMeasure state#NowPlayingMedia# "ToggleThumbsDown"]
[EmptyHeart]
ImageName=#@#Icons\Heart.png
LeftMouseUpAction=[!SetOption #CURRENTSECTION# MeterStyle "Sec.BottomButton:S | Fullheart"][!UpdateMeter #CURRENTSECTION#]#MHC_Reset#[!CommandMeasure state#NowPlayingMedia# "ToggleThumbsUp"]


[MediaHoverCircle]
Meter=Shape
Shape=Ellipse (10*#scale#),(10*#scale#),(17*#Scale#) | StrokeWidth 0 | Extend Fill
Fill=Fill Color #FontCOlor#,20
Container=MediaC
Hidden=1

; ---------------------------------------------------------------------------- ;
;                                    Special                                   ;
; ---------------------------------------------------------------------------- ;

; ----------------------------------- Caps ----------------------------------- ;

[LocksB]
Meter=Shape
X=1
Y=1
Shape=Rectangle 0,0,#LocksW#,#LocksW#,#R# | StrokeWidth #Stroke# | Fill Color #PrimaryColor#,#PrimaryOpacity# | Stroke Color #SecondaryColor#,#SecondaryOpacity#
Group=Locks | Special
Hidden=1
[LocksC]
Meter=Shape
X=r
Y=r
Shape=Rectangle 0,0,#LocksW#,#LocksW#,#R# | StrokeWidth 0 | Fill Color 255,255,255,(255*#TweenNode1#)
Group=Locks | Special | Animated
DynamicVariables=1
Hidden=1


[LocksIcon]
Meter=String
MeterStyle=String:S
X=(#LocksW#/2)
Y=(#LocksW#/2)
FontFace=Material Icons Round
StringAlign=CenterCenter
FontWeight=650
FontSize=(80*#scale#*#TweenNode1#)
DynamicVariables=1
Group=Locks | Special | Animated
Container=LocksC

[LocksText]
Meter=String
MeterStyle=String:S
X=r
Y=(#LocksW#-#P#)
W=(#LocksW#)
StringAlign=CenterBottom
ClipString=2
InlineSetting=Shadow | 0 | 0 | 5 | #FontColor#,50
FontSize=(10*#scale#)
Group=Locks | Special
Container=LocksC
Hidden=1


[LocksIcon.On:S]
Text=[\xe837]
InlineSetting=GradientColor | 45 | #AccentColor1# ; 0 | #FontColor# ; 1
InlineSetting2=Shadow | 0 | 0 | 3 | #FontColor#
InlineSetting3=Shadow | 0 | 0 | 5 | #AccentColor1#
[LocksIcon.Off:S]
Text=[\xe836]
FontColor=#FontColor2#
InlineSetting=Shadow | 0 | 0 | 5 | #FontColor#,50
[LocksText.CapsLock.On:S]
Text=Toggled CapsLock On
Fontcolor=#FontColor#
[LocksText.CapsLock.Off:S]
Text=Toggled CapsLock Off
Fontcolor=#FontColor2#
[LocksText.ScrollLock.On:S]
Text=Toggled ScrollLock On
Fontcolor=#FontColor#
[LocksText.ScrollLock.Off:S]
Text=Toggled ScrollLock Off
Fontcolor=#FontColor2#
[LocksText.NumLock.On:S]
Text=Toggled NumLock On
Fontcolor=#FontColor#
[LocksText.NumLock.Off:S]
Text=Toggled NumLock Off
Fontcolor=#FontColor2#