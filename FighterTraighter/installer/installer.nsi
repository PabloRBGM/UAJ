!include "MUI2.nsh"


Name "Fighter Traighter"
OutFile "Fighter Traighter setup.exe"
Unicode True
InstallDir "$PROGRAMFILES64\Fighter Traighter"
RequestExecutionLevel admin

Var StartMenuFolder
Var "FTName"

!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "..\assets\Assets\images\installer\header_bitmap.bmp" ; NOTE: images have to be 8 bits in depth
!define MUI_HEADERIMAGE_UNBITMAP "..\assets\Assets\images\installer\header_bitmap.bmp" ; NOTE: images have to be 8 bits in depth

!define MUI_WELCOMEFINISHPAGE_BITMAP "..\assets\Assets\images\installer\welcomepage_bitmap.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "..\assets\Assets\images\installer\welcomepage_bitmap.bmp"

Function finishpageaction
	CreateShortcut "$desktop\$FTName.lnk" "$INSTDIR\DELETE\ME\IM\USELESS\MF-FighterTraighter.exe"
FunctionEnd

!define MUI_FINISHPAGE_SHOWREADME ""
!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Create Desktop Shortcut"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION finishpageaction

!insertmacro MUI_PAGE_WELCOME
; !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt" ; PLACE A LICENSE
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Fighter $StartMenuFolder
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section

	StrCpy $FTName "Fighter Traighter"
	
    # set the directory and files to go to the output directory
	
    SetOutPath $INSTDIR\DELETE\ME\IM\USELESS

	File "..\src\MF-FighterTraighter\x64\Release\MF-FighterTraighter.exe"
	File "..\src\MF-FighterTraighter\x64\Release\MF-FighterTraighter.iobj"
	File "..\src\MF-FighterTraighter\x64\Release\MF-FighterTraighter.ipdb"
	File "..\src\MF-FighterTraighter\x64\Release\MF-FighterTraighter.pdb"
	File "..\src\MF-FighterTraighter\x64\Release\libFLAC-8.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libfreetype-6.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libjpeg-9.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libmodplug-1.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libmpg123-0.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libogg-0.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libopus-0.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libopusfile-0.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libpng16-16.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libtiff-5.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libvorbis-0.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libvorbisfile-3.dll"
	File "..\src\MF-FighterTraighter\x64\Release\libwebp-7.dll"
	File "..\src\MF-FighterTraighter\x64\Release\SDL2.dll"
	File "..\src\MF-FighterTraighter\x64\Release\SDL2_image.dll"
	File "..\src\MF-FighterTraighter\x64\Release\SDL2_mixer.dll"
	File "..\src\MF-FighterTraighter\x64\Release\SDL2_ttf.dll"
	File "..\src\MF-FighterTraighter\x64\Release\zlib1.dll"
	
	SetOutPath $INSTDIR\assets\Assets\Fonts
	
	File "..\assets\Assets\Fonts\Roboto-Black.ttf"

	SetOutPath $INSTDIR\assets\Assets\Sounds\Songs

	File "..\assets\Assets\Sounds\Songs\New Hope menu.ogg"
	File "..\assets\Assets\Sounds\Songs\Never Surrender.ogg"
	File "..\assets\Assets\Sounds\Songs\Boss Fight.ogg"
	
	SetOutPath $INSTDIR\assets\Assets\Sounds\Taunts\MKW00P
	
	File "..\assets\Assets\Sounds\Taunts\MKW00P\buzz.wav"
	File "..\assets\Assets\Sounds\Taunts\MKW00P\clonk.wav"
	File "..\assets\Assets\Sounds\Taunts\MKW00P\piribi.wav"
	File "..\assets\Assets\Sounds\Taunts\MKW00P\robotau.wav"

	SetOutPath $INSTDIR\assets\Assets\Sounds\Taunts\F10R
	
	File "..\assets\Assets\Sounds\Taunts\F10R\zombidolor.mp3"

	SetOutPath $INSTDIR\assets\Assets\Sounds\Taunts\Mockingbird
	
	File "..\assets\Assets\Sounds\Taunts\Mockingbird\ouch.wav"
	File "..\assets\Assets\Sounds\Taunts\Mockingbird\pain.wav"
	File "..\assets\Assets\Sounds\Taunts\Mockingbird\yeow.wav"
	
	SetOutPath $INSTDIR\assets\Assets\Sounds\SFX
	
	File "..\assets\Assets\Sounds\SFX\florAttack3.wav"
	File "..\assets\Assets\Sounds\SFX\florAttack2.ogg"
	File "..\assets\Assets\Sounds\SFX\salto.wav"
	File "..\assets\Assets\Sounds\SFX\rocas.wav"
	File "..\assets\Assets\Sounds\SFX\powerup2.wav"
	File "..\assets\Assets\Sounds\SFX\lanzar.wav"
	File "..\assets\Assets\Sounds\SFX\tambor.wav"
	File "..\assets\Assets\Sounds\SFX\cristal.wav"
	File "..\assets\Assets\Sounds\SFX\lanzamiento4.wav"
	File "..\assets\Assets\Sounds\SFX\burbuja2.wav"
	File "..\assets\Assets\Sounds\SFX\powerup1.wav"
	File "..\assets\Assets\Sounds\SFX\explosionretro.wav"
	File "..\assets\Assets\Sounds\SFX\punch.wav"
	File "..\assets\Assets\Sounds\SFX\gancho.wav"
	File "..\assets\Assets\Sounds\SFX\patada.wav"
	File "..\assets\Assets\Sounds\SFX\failattack.wav"
	File "..\assets\Assets\Sounds\SFX\pollo.wav"
	File "..\assets\Assets\Sounds\SFX\mina.wav"
	File "..\assets\Assets\Sounds\SFX\hielo.wav"
	File "..\assets\Assets\Sounds\SFX\laser3.wav"
	File "..\assets\Assets\Sounds\SFX\laser1.wav"
	File "..\assets\Assets\Sounds\SFX\boton.wav"
	File "..\assets\Assets\Sounds\SFX\ataque.wav"
	File "..\assets\Assets\Sounds\SFX\ataque2.wav"
	File "..\assets\Assets\Sounds\SFX\placaje.wav"
	File "..\assets\Assets\Sounds\SFX\floorAttack.wav"
	File "..\assets\Assets\Sounds\SFX\floorAttack2.wav"
	File "..\assets\Assets\Sounds\SFX\normalpunch.wav"
	File "..\assets\Assets\Sounds\SFX\hit.wav"
	File "..\assets\Assets\Sounds\SFX\hit2.wav"
	File "..\assets\Assets\Sounds\SFX\flykick.wav"
	File "..\assets\Assets\Sounds\SFX\vampiric.wav"
	File "..\assets\Assets\Sounds\SFX\cuchillo.mp3"
	File "..\assets\Assets\Sounds\SFX\arena.mp3"
	
	SetOutPath $INSTDIR\assets\Assets\
	
	File "..\assets\Assets\personaje.png"
	File "..\assets\Assets\personajeActing.png"

	SetOutPath $INSTDIR\assets\Assets\images
	
	File "..\assets\Assets\images\backgroundtemp.png"
	File "..\assets\Assets\images\warbanner.png"
	File "..\assets\Assets\images\FONDO.png"
	File "..\assets\Assets\images\flor_bg.png"
	File "..\assets\Assets\images\floortemp.png"
	File "..\assets\Assets\images\floortempflor.png"
	File "..\assets\Assets\images\panel.png"
	File "..\assets\Assets\images\submenuFondo.jpg"
	File "..\assets\Assets\images\submenuwin.jpg"
	
	SetOutPath $INSTDIR\assets\Assets\images\UI
	
	File "..\assets\Assets\images\UI\buttons.png"
	File "..\assets\Assets\images\UI\logo.png"
	File "..\assets\Assets\images\UI\Tint.png"
	File "..\assets\Assets\images\UI\controller.png"
	File "..\assets\Assets\images\UI\slidebar.png"
	File "..\assets\Assets\images\UI\regulador.png"
	File "..\assets\Assets\images\UI\characters_selection.png"
	File "..\assets\Assets\images\UI\healthbar.png"
	File "..\assets\Assets\images\UI\healthbarSaco.png"
	File "..\assets\Assets\images\UI\healthbarBack.png"
	File "..\assets\Assets\images\UI\RoundCounter.png"
	File "..\assets\Assets\images\UI\marco1.png"
	File "..\assets\Assets\images\UI\marco2.png"

	SetOutPath $INSTDIR\assets\Assets\images\characters
	
	File "..\assets\Assets\images\characters\saco.png"
	File "..\assets\Assets\images\characters\sacoNoSombra.png"
	File "..\assets\Assets\images\characters\flor_spritesheet.png"
	File "..\assets\Assets\images\characters\Ganonbot_spritesheet.png"
	File "..\assets\Assets\images\characters\mockingbird-spritesheet.png"
	
	SetOutPath "$INSTDIR\assets\Assets\images\selection characters"
	
	File "..\assets\Assets\images\selection characters\aisha-icon.png"
	File "..\assets\Assets\images\selection characters\aisha.png"
	File "..\assets\Assets\images\selection characters\flor-icon.png"
	File "..\assets\Assets\images\selection characters\flor.png"
	File "..\assets\Assets\images\selection characters\ganonbot-icon.png"
	File "..\assets\Assets\images\selection characters\ganonbot.png"
	File "..\assets\Assets\images\selection characters\moc-icon.png"
	File "..\assets\Assets\images\selection characters\mock.png"
	File "..\assets\Assets\images\selection characters\Random-icon.png"
	File "..\assets\Assets\images\selection characters\random.png"
	File "..\assets\Assets\images\selection characters\imagenMenu.png"
	File "..\assets\Assets\images\selection characters\recuadro.png"
	
	SetOutPath $INSTDIR\assets\Assets\images\attacks

	File "..\assets\Assets\images\attacks\F10RHp.png"
	File "..\assets\Assets\images\attacks\F10RHk.png"
	File "..\assets\Assets\images\attacks\MkWH00PHk.png"
	File "..\assets\Assets\images\attacks\MOCKAHK.png"
	
	SetOutPath $INSTDIR\assets\Assets\images\skills\iconos

	File "..\assets\Assets\images\skills\iconos\so1.png"
	File "..\assets\Assets\images\skills\iconos\ReachingStrikeIcon.png"
	File "..\assets\Assets\images\skills\iconos\doping.png"
	File "..\assets\Assets\images\skills\iconos\pollo.png"
	File "..\assets\Assets\images\skills\iconos\poison syrup.png"
	File "..\assets\Assets\images\skills\iconos\dash.png"
	File "..\assets\Assets\images\skills\iconos\Vampiric_ico.png"
	File "..\assets\Assets\images\skills\iconos\LaserLineal_ico.png"
	File "..\assets\Assets\images\skills\iconos\mina2.png"
	File "..\assets\Assets\images\skills\iconos\Ganchoicon.png"
	File "..\assets\Assets\images\skills\iconos\hielo.png"
	File "..\assets\Assets\images\skills\iconos\knockout.png"
	File "..\assets\Assets\images\skills\iconos\ExplosiveWillPower.png"
	File "..\assets\Assets\images\skills\iconos\PatadasVoladoras.png"
	File "..\assets\Assets\images\skills\iconos\NadoKick_ico.png"
	File "..\assets\Assets\images\skills\iconos\MegatonGrip.png"
	File "..\assets\Assets\images\skills\iconos\Seismicshock.png"
	File "..\assets\Assets\images\skills\iconos\RandomRage.png"
	File "..\assets\Assets\images\skills\iconos\KnifeDance.png"
	; File "..\assets\Assets\images\skills\iconos\doping.png"
	
	SetOutPath $INSTDIR\assets\Assets\images\skills\
	
	; File "..\assets\Assets\images\skills\pollo.png"
	File "..\assets\Assets\images\skills\mg1.png"
	File "..\assets\Assets\images\skills\mg2-1.png"
	File "..\assets\Assets\images\skills\mg2-2.png"
	File "..\assets\Assets\images\skills\ss1.png"
	File "..\assets\Assets\images\skills\ss2.png"
	File "..\assets\Assets\images\skills\ew1.png"
	File "..\assets\Assets\images\skills\pollo.png"
	File "..\assets\Assets\images\skills\so1.png"
	File "..\assets\Assets\images\skills\mp1.png"
	File "..\assets\Assets\images\skills\hs1.png"
	File "..\assets\Assets\images\skills\as2.png"
	File "..\assets\Assets\images\skills\mina1.png"
	; File "..\assets\Assets\images\skills\mina2.png"
	File "..\assets\Assets\images\skills\minafinal.png"
	; File "..\assets\Assets\images\skills\pollo.png"
	File "..\assets\Assets\images\skills\vs1.png"
	File "..\assets\Assets\images\skills\vs2.png"
	File "..\assets\Assets\images\skills\hb1.png"
	File "..\assets\Assets\images\skills\hb2.png"
	File "..\assets\Assets\images\skills\laserlineal-2.png"
	File "..\assets\Assets\images\skills\FK1.png"
	File "..\assets\Assets\images\skills\FK4.png"
	File "..\assets\Assets\images\skills\acidPotion.png"
	File "..\assets\Assets\images\skills\ReachingStrike.png"
	File "..\assets\Assets\images\skills\nk1.png"
	File "..\assets\Assets\images\skills\kd1.png"


	#end of files
 
 
    # create the uninstaller
    WriteUninstaller "$INSTDIR\uninstall $FTName.exe"
	
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Fighter
	
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortcut "$SMPROGRAMS\$StartMenuFolder\uninstall $FTName.lnk" "$INSTDIR\uninstall $FTName.exe"
    CreateShortcut "$SMPROGRAMS\$StartMenuFolder\$FTName.lnk" "$INSTDIR\DELETE\ME\IM\USELESS\MF-FighterTraighter.exe"
	
	!insertmacro MUI_STARTMENU_WRITE_END

SectionEnd

# uninstaller section start
Section "Uninstall"
 
 	StrCpy $FTName "Fighter Traighter"
	
    # first, delete the uninstaller
    Delete "$INSTDIR\uninstall $FTName.exe"
	
	# second, remove the link from the start menu	
   !insertmacro MUI_STARTMENU_GETFOLDER Fighter $StartMenuFolder
   
    Delete "$SMPROGRAMS\$StartMenuFolder\uninstall $FTName.lnk"
    Delete "$SMPROGRAMS\$StartMenuFolder\$FTName.lnk"
	Delete "$desktop\$FTName.lnk"
	RMDir "$SMPROGRAMS\$StartMenuFolder"
	
	# now delete installed files
	
	Delete $INSTDIR\DELETE\ME\IM\USELESS\MF-FighterTraighter.exe
	Delete $INSTDIR\DELETE\ME\IM\USELESS\MF-FighterTraighter.iobj
	Delete $INSTDIR\DELETE\ME\IM\USELESS\MF-FighterTraighter.ipdb
	Delete $INSTDIR\DELETE\ME\IM\USELESS\MF-FighterTraighter.pdb
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libFLAC-8.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libfreetype-6.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libjpeg-9.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libmodplug-1.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libmpg123-0.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libogg-0.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libopus-0.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libopusfile-0.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libpng16-16.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libtiff-5.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libvorbis-0.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libvorbisfile-3.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\libwebp-7.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\SDL2.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\SDL2_image.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\SDL2_mixer.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\SDL2_ttf.dll
	Delete $INSTDIR\DELETE\ME\IM\USELESS\zlib1.dll
	
	Delete $INSTDIR\assets\Assets\Fonts\Roboto-Black.ttf
	
	Delete "$INSTDIR\assets\Assets\Sounds\Songs\New Hope menu.ogg"
	Delete "$INSTDIR\assets\Assets\Sounds\Songs\Never Surrender.ogg"
	Delete "$INSTDIR\assets\Assets\Sounds\Songs\Boss Fight.ogg"
	
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\MKW00P\buzz.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\MKW00P\clonk.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\MKW00P\piribi.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\MKW00P\robotau.wav"
	
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\F10R\zombidolor.mp3"
	
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\Mockingbird\ouch.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\Mockingbird\pain.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\Taunts\Mockingbird\yeow.wav"

	Delete "$INSTDIR\assets\Assets\Sounds\SFX\florAttack3.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\florAttack2.ogg"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\salto.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\rocas.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\powerup2.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\lanzar.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\tambor.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\cristal.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\lanzamiento4.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\burbuja2.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\powerup1.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\explosionretro.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\punch.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\gancho.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\patada.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\failattack.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\pollo.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\mina.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\hielo.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\laser3.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\laser1.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\boton.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\ataque.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\ataque2.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\placaje.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\floorAttack.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\floorAttack2.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\normalpunch.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\hit.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\hit2.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\flykick.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\vampiric.wav"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\cuchillo.mp3"
	Delete "$INSTDIR\assets\Assets\Sounds\SFX\arena.mp3"
	
	Delete "$INSTDIR\assets\Assets\personaje.png"
	Delete "$INSTDIR\assets\Assets\personajeActing.png"
	
	Delete "$INSTDIR\assets\Assets\images\backgroundtemp.png"
	Delete "$INSTDIR\assets\Assets\images\warbanner.png"
	Delete "$INSTDIR\assets\Assets\images\FONDO.png"
	Delete "$INSTDIR\assets\Assets\images\flor_bg.png"
	Delete "$INSTDIR\assets\Assets\images\floortemp.png"
	Delete "$INSTDIR\assets\Assets\images\floortempflor.png"
	Delete "$INSTDIR\assets\Assets\images\panel.png"
	Delete "$INSTDIR\assets\Assets\images\submenuFondo.jpg"
	Delete "$INSTDIR\assets\Assets\images\submenuwin.jpg"
	
	Delete "$INSTDIR\assets\Assets\images\UI\buttons.png"
	Delete "$INSTDIR\assets\Assets\images\UI\logo.png"
	Delete "$INSTDIR\assets\Assets\images\UI\Tint.png"
	Delete "$INSTDIR\assets\Assets\images\UI\controller.png"
	Delete "$INSTDIR\assets\Assets\images\UI\slidebar.png"
	Delete "$INSTDIR\assets\Assets\images\UI\regulador.png"
	Delete "$INSTDIR\assets\Assets\images\UI\characters_selection.png"
	Delete "$INSTDIR\assets\Assets\images\UI\healthbar.png"
	Delete "$INSTDIR\assets\Assets\images\UI\healthbarSaco.png"
	Delete "$INSTDIR\assets\Assets\images\UI\healthbarBack.png"
	Delete "$INSTDIR\assets\Assets\images\UI\RoundCounter.png"
	Delete "$INSTDIR\assets\Assets\images\UI\marco1.png"
	Delete "$INSTDIR\assets\Assets\images\UI\marco2.png"
	
	Delete "$INSTDIR\assets\Assets\images\characters\saco.png"
	Delete "$INSTDIR\assets\Assets\images\characters\sacoNoSombra.png"
	Delete "$INSTDIR\assets\Assets\images\characters\flor_spritesheet.png"
	Delete "$INSTDIR\assets\Assets\images\characters\Ganonbot_spritesheet.png"
	Delete "$INSTDIR\assets\Assets\images\characters\mockingbird-spritesheet.png"
	
	Delete "$INSTDIR\assets\Assets\images\selection characters\aisha-icon.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\aisha.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\flor-icon.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\flor.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\ganonbot-icon.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\ganonbot.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\moc-icon.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\mock.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\Random-icon.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\random.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\imagenMenu.png"
	Delete "$INSTDIR\assets\Assets\images\selection characters\recuadro.png"
	
	Delete "$INSTDIR\assets\Assets\images\attacks\F10RHp.png"
	Delete "$INSTDIR\assets\Assets\images\attacks\F10RHk.png"
	Delete "$INSTDIR\assets\Assets\images\attacks\MkWH00PHk.png"
	Delete "$INSTDIR\assets\Assets\images\attacks\MOCKAHK.png"
	
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\so1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\ReachingStrikeIcon.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\doping.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\pollo.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\poison syrup.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\dash.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\Vampiric_ico.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\LaserLineal_ico.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\mina2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\Ganchoicon.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\hielo.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\knockout.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\ExplosiveWillPower.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\PatadasVoladoras.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\NadoKick_ico.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\MegatonGrip.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\Seismicshock.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\RandomRage.png"
	Delete "$INSTDIR\assets\Assets\images\skills\iconos\KnifeDance.png"
	; Delete "$INSTDIR\assets\Assets\images\skills\iconos\doping.png"
	
	; Delete "$INSTDIR\assets\Assets\images\skills\pollo.png"
	Delete "$INSTDIR\assets\Assets\images\skills\mg1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\mg2-1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\mg2-2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\ss1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\ss2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\ew1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\pollo.png"
	Delete "$INSTDIR\assets\Assets\images\skills\so1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\mp1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\hs1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\as2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\mina1.png"
	; Delete "$INSTDIR\assets\Assets\images\skills\mina2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\minafinal.png"
	; Delete "$INSTDIR\assets\Assets\images\skills\pollo.png"
	Delete "$INSTDIR\assets\Assets\images\skills\vs1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\vs2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\hb1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\hb2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\laserlineal-2.png"
	Delete "$INSTDIR\assets\Assets\images\skills\FK1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\FK4.png"
	Delete "$INSTDIR\assets\Assets\images\skills\acidPotion.png"
	Delete "$INSTDIR\assets\Assets\images\skills\ReachingStrike.png"
	Delete "$INSTDIR\assets\Assets\images\skills\nk1.png"
	Delete "$INSTDIR\assets\Assets\images\skills\kd1.png"
	
	#end of files
 
 
	# Delete all directories
	
	RMDir $INSTDIR\DELETE\ME\IM\USELESS
	RMDir $INSTDIR\DELETE\ME\IM
	RMDir $INSTDIR\DELETE\ME
	RMDir $INSTDIR\DELETE
	RMDir $INSTDIR\assets\Assets\Fonts
	RMDir $INSTDIR\assets\Assets\Sounds\Songs
	RMDir $INSTDIR\assets\Assets\Sounds\Taunts\MKW00P
	RMDir $INSTDIR\assets\Assets\Sounds\Taunts\F10R
	RMDir $INSTDIR\assets\Assets\Sounds\Taunts\Mockingbird
	RMDir $INSTDIR\assets\Assets\Sounds\Taunts
	RMDir $INSTDIR\assets\Assets\Sounds\SFX
	RMDir $INSTDIR\assets\Assets\Sounds
	RMDir $INSTDIR\assets\Assets\images\UI
	RMDir $INSTDIR\assets\Assets\images\characters
	RMDir "$INSTDIR\assets\Assets\images\selection characters"
	RMDir $INSTDIR\assets\Assets\images\attacks
	RMDir $INSTDIR\assets\Assets\images\skills\iconos
	RMDir $INSTDIR\assets\Assets\images\skills
	RMDir $INSTDIR\assets\Assets\images
	RMDir $INSTDIR\assets\Assets
	RMDir $INSTDIR\assets
    RMDir $INSTDIR

	
# uninstaller section end
SectionEnd