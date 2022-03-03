#include "AssetsManager.h"
#include "App.h"

AssetsManager::AssetsManager(App* app) : app_(app)
{

	loadTextures();
	loadFonts();
	loadMusic();
	loadSFX();
}

Texture* AssetsManager::getTexture(AssetsManager::TextureNames id)
{
	return textures_[id];
}

void AssetsManager::loadTextures()
{
	textures_.emplace(EmptyHability, new Texture(app_->getRenderer(), "../../../../assets/Assets/personaje.png", 1, 1));
	textures_.emplace(Saco, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/characters/saco.png", 1, 1));
	textures_.emplace(Button, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/buttons.png", 3, 1));
	textures_.emplace(Logo, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/logo.png", 1, 1));
	textures_.emplace(Tint, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/Tint.png", 1, 1));
	textures_.emplace(Controller, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/controller.png", 1, 1));
	textures_.emplace(saco2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/characters/sacoNoSombra.png", 1, 1));
	
	textures_.emplace(Slidebar, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/slidebar.png", 1, 1));
	textures_.emplace(SliderRegulator, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/regulador.png", 2, 1));
	textures_.emplace(PlayerActing, new Texture(app_->getRenderer(), "../../../../assets/Assets/personajeActing.png", 1, 1));
	
	textures_.emplace(Background, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/backgroundtemp.png", 1, 1));
	textures_.emplace(CharacterSelection, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/characters_selection.png", 4, 1));
	textures_.emplace(Banner, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/warbanner.png", 1, 1)); 

	//backgrounds
	textures_.emplace(BackgroundFight, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/FONDO.png", 2, 1));
	textures_.emplace(BackgroundFloor, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/flor_bg.png", 2, 1));
	textures_.emplace(floor, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/floortemp.png", 1, 1));
	textures_.emplace(floorIA, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/floortempflor.png", 1, 1));

	
	//UI elements
		//healthbar
	textures_.emplace(Healthbar, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/healthbar.png", 1, 1));
	textures_.emplace(HealthbarSaco, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/healthbarSaco.png", 1, 1));
	textures_.emplace(HealthbarBack, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/healthbarBack.png", 1, 1));
		//roundcounter
	textures_.emplace(RoundCounter, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/RoundCounter.png", 2, 1));

	//aisha resources
	textures_.emplace(Aisha_icon, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/aisha-icon.png", 2, 1)); 
	textures_.emplace(AishaArtwork, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/aisha.png", 1, 1)); 
	
	//flor resources
	textures_.emplace(Flor_icon, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/flor-icon.png", 2, 1));
	textures_.emplace(FlorArtwork, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/flor.png", 1, 1));
	textures_.emplace(F10rSheet, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/characters/flor_spritesheet.png", 6, 25));
	textures_.emplace(F10RHp, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/attacks/F10RHp.png", 1, 1));
	textures_.emplace(F10RHk, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/attacks/F10RHk.png", 1, 1));

	//ganon resources
	textures_.emplace(Ganonbot_icon, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/ganonbot-icon.png", 2, 1)); 
	textures_.emplace(GanonArtwork, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/ganonbot.png", 1, 1)); 
	textures_.emplace(GanonSheet, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/characters/Ganonbot_spritesheet.png", 15, 23));

	textures_.emplace(MkHk, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/attacks/MkWH00PHk.png", 1, 1));
	
	//mockingbird resources
	textures_.emplace(Mock_icon, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/moc-icon.png", 2, 1));  
	textures_.emplace(MockArtwork, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/mock.png", 1, 1));  
	textures_.emplace(MockSheet, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/characters/mockingbird-spritesheet.png", 6, 24));  
	textures_.emplace(MockAHK, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/attacks/MOCKAHK.png",1,1));  

	textures_.emplace(Random_icon, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/Random-icon.png", 2, 1));
	textures_.emplace(RandomArtwork, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/random.png", 1, 1));
	
	textures_.emplace(Panel, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/panel.png", 1, 1)); 
	textures_.emplace(CollageCharacters, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/imagenMenu.png", 1, 1));

	//ability icons
	textures_.emplace(ShrugOff_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/so1.png", 1, 1));
	textures_.emplace(Reach_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/ReachingStrikeIcon.png", 1, 1));
	textures_.emplace(MorePower_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/doping.png", 2, 1));
	textures_.emplace(Chicken_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/pollo.png", 1, 1));
	textures_.emplace(Acid_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/poison syrup.png", 2, 1));
	textures_.emplace(Dash_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/dash.png", 1, 1));
	textures_.emplace(Vampiric_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/Vampiric_ico.png", 1, 1));
	textures_.emplace(L_Lineal_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/LaserLineal_ico.png", 1, 1));
	textures_.emplace(Mina_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/mina2.png", 1, 1));
	textures_.emplace(Hook_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/Ganchoicon.png", 1, 1));
	textures_.emplace(HailBall_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/hielo.png", 2, 1));
	textures_.emplace(Knockdown_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/knockout.png", 1, 1));
	textures_.emplace(Ex_Will_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/ExplosiveWillPower.png", 1, 1));
	textures_.emplace(FlyingKicks_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/PatadasVoladoras.png", 1, 1));
	textures_.emplace(Nado_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/NadoKick_ico.png", 1, 1));
	textures_.emplace(M_Grip_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/MegatonGrip.png", 1, 1));
	textures_.emplace(S_Sock_ico, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/Seismicshock.png", 1, 1));
	textures_.emplace(RandomRage, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/RandomRage.png", 1, 1));
	textures_.emplace(KnifeDance, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/KnifeDance.png", 1, 1));
	textures_.emplace(Doping, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/iconos/doping.png", 2, 1));

	//creo que hasta aqui los iconos

	textures_.emplace(Mark1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/marco1.png", 1, 1));
	textures_.emplace(Mark2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/UI/marco2.png", 1, 1));
	textures_.emplace(Mg1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/mg1.png", 1, 1));
	textures_.emplace(Mg21, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/mg2-1.png", 1, 1));
	textures_.emplace(Mg22, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/mg2-2.png", 1, 1));
	textures_.emplace(Ss1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/ss1.png", 1, 1));
	textures_.emplace(Ss2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/ss2.png", 1, 1));
	textures_.emplace(Ew1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/ew1.png", 1, 1));

	textures_.emplace(Pollo, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/pollo.png", 1, 1));
	
	textures_.emplace(Celda1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/submenuFondo.jpg", 1, 1));
	textures_.emplace(Celda2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/submenuwin.jpg", 1, 1));
	textures_.emplace(So1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/so1.png", 1, 1));
	textures_.emplace(Mp1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/mp1.png", 1, 1));
		
	textures_.emplace(Hs1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/hs1.png", 1, 1));
	textures_.emplace(As2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/as2.png", 4, 1));
	textures_.emplace(M1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/mina1.png", 1, 1));
	//textures_.emplace(M2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/mina2.png", 1, 1));
	textures_.emplace(M3, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/minafinal.png", 2, 1));
	textures_.emplace(PO1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/pollo.png", 1, 1));
	textures_.emplace(Vs1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/vs1.png", 1, 1));
	textures_.emplace(Vs2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/vs2.png", 1, 1));
	textures_.emplace(Hb1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/hb1.png", 1, 1));
	textures_.emplace(Hb2, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/hb2.png", 1, 1));
	textures_.emplace(Ll1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/laserlineal-2.png", 1, 1));
	textures_.emplace(FK1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/FK1.png", 1, 1));
	textures_.emplace(FK4, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/FK4.png", 1, 1));
	textures_.emplace(AS1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/acidPotion.png", 1, 1));
	textures_.emplace(Rs1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/ReachingStrike.png", 1, 1));
	textures_.emplace(nk1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/nk1.png", 2, 1));
	textures_.emplace(kd1, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/skills/kd1.png", 1, 1));

	// textures_.emplace("key", new Texture(app_->getRenderer(), "Filepath", cols, fils));
	textures_.emplace(SelectionSquare, new Texture(app_->getRenderer(), "../../../../assets/Assets/images/selection characters/recuadro.png", 1, 1));
}

Font* AssetsManager::getFont(AssetsManager::FontNames id)
{
	return fonts_[id];
}

void AssetsManager::loadFonts()
{
	fonts_.emplace(Roboto_Black, new Font("../../../../assets/Assets/Fonts/Roboto-Black.ttf", 300, 0.5));
	// fonts_.emplace_back(new Font("Filepath", size));
}

Mix_Music* AssetsManager::getMusic(AssetsManager::MusicNames id)
{
	return music_[id];
}

void AssetsManager::loadMusic()
{
	//size_t id = 1;

	music_.emplace(MENU_PRINCIPAL, app_->getAudioMngr()->loadMusic("../../../../assets/Assets/Sounds/Songs/New Hope menu.ogg"));
	music_.emplace(MENU_OPCIONES, app_->getAudioMngr()->loadMusic("../../../../assets/Assets/Sounds/Songs/Never Surrender.ogg"));
	music_.emplace(FIGHT_1, app_->getAudioMngr()->loadMusic("../../../../assets/Assets/Sounds/Songs/Boss Fight.ogg"));
	//music_.emplace(Nombre,app_->getAudioManager()->loadMusic("../../../../assets/Assets/Sounds/Songs/nombre de la cancion. formato"));

}

Mix_Chunk* AssetsManager::getSFX(AssetsManager::SFXNames id)
{	
	return sfx_[id];
}
void AssetsManager::loadSFX()
{
	
	sfx_.emplace(MKWOP_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/MKW00P/buzz.wav"));
	sfx_.emplace(MKWOP_2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/MKW00P/clonk.wav"));
	sfx_.emplace(MKWOP_3, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/MKW00P/piribi.wav"));
	sfx_.emplace(MKWOP_4, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/MKW00P/robotau.wav"));

	sfx_.emplace(FLOR_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/F10R/zombidolor.mp3"));
	sfx_.emplace(FLOR_2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/florAttack3.wav"));
	sfx_.emplace(FLOR_3, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/florAttack2.ogg"));

	sfx_.emplace(MKBIRD_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/Mockingbird/ouch.wav"));
	sfx_.emplace(MKBIRD_2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/Mockingbird/pain.wav"));
	sfx_.emplace(MKBIRD_3, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/Taunts/Mockingbird/yeow.wav"));

	/*sfx_.emplace(AISHA_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/punch.wav"));
	sfx_.emplace(AISHA_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/punch.wav"));
	sfx_.emplace(AISHA_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/punch.wav"));
	sfx_.emplace(AISHA_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/punch.wav"));
	sfx_.emplace(AISHA_1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/punch.wav"));*/
	sfx_.emplace(SALTO, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/salto.wav"));
	sfx_.emplace(ROCAS, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/rocas.wav"));
	sfx_.emplace(POWER2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/powerup2.wav"));
	sfx_.emplace(LANZAR, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/lanzar.wav"));
	sfx_.emplace(EWP, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/tambor.wav"));
	sfx_.emplace(CRISTAL, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/cristal.wav"));
	sfx_.emplace(LANZAR4, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/lanzamiento4.wav"));
	sfx_.emplace(BURBUJA, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/burbuja2.wav"));
	sfx_.emplace(POWER1, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/powerup1.wav"));
	sfx_.emplace(EXPLOSION, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/explosionretro.wav"));

	sfx_.emplace(PUNCH, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/punch.wav"));
	sfx_.emplace(GANCHO, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/gancho.wav"));
	sfx_.emplace(KICK, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/patada.wav"));
	sfx_.emplace(DASH, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/failattack.wav"));
	sfx_.emplace(POLLO, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/pollo.wav"));
	sfx_.emplace(MINA, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/mina.wav"));
	sfx_.emplace(HIELO, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/hielo.wav"));
	sfx_.emplace(LASER, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/laser3.wav"));
	sfx_.emplace(GBMKW00P, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/laser1.wav"));
	sfx_.emplace(BOTON, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/boton.wav"));
	sfx_.emplace(ATAQUE2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/ataque.wav"));
	sfx_.emplace(ATAQUE, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/ataque2.wav"));
	sfx_.emplace(PLACAJE, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/placaje.wav")); 
	sfx_.emplace(FLOORATTACK, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/floorAttack.wav"));
	sfx_.emplace(FLOORATTACK2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/floorAttack2.wav"));
	sfx_.emplace(PUNCH2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/normalpunch.wav"));
	sfx_.emplace(HIT, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/hit.wav"));
	sfx_.emplace(HIT2, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/hit2.wav"));
	sfx_.emplace(NORMALPUNCH, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/flykick.wav"));
	sfx_.emplace(VAMPIRIC, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/vampiric.wav"));
	sfx_.emplace(KNIFE, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/cuchillo.mp3"));
	sfx_.emplace(SAND, app_->getAudioMngr()->loadSFX("../../../../assets/Assets/Sounds/SFX/arena.mp3"));

}

AssetsManager::~AssetsManager()
{
	UnloadAssets();
}

void AssetsManager::UnloadAssets()
{
	for (auto tex = textures_.begin(); tex != textures_.end(); ++tex) {
		delete tex->second;
	}
	for (auto font = fonts_.begin(); font != fonts_.end(); ++font) {
		delete font->second;
	}

}
