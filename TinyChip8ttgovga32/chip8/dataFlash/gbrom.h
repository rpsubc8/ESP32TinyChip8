#ifndef _GB_ROM_H
 #define _GB_ROM_H

 #include <stddef.h>
 #include "roms/rom15PUZZLE.h"
 #include "roms/romAdditionProb.h"
 #include "roms/romAirplane.h"
 #include "roms/romAnimalRace.h"
 #include "roms/romAstroDodge.h"
 #include "roms/romBiorhythmJef.h"
 #include "roms/romBLINKY.h"
 #include "roms/romBLITZ.h"
 #include "roms/romBMPViewerHel.h"
 #include "roms/romBowlingGooit.h"
 #include "roms/romBreakoutBrix.h"
 #include "roms/romBRIX.h"
 #include "roms/romCave.h"
 #include "roms/romChip8emulato.h"
 #include "roms/romChip8Picture.h"
 #include "roms/romClockProgram.h"
 #include "roms/romCoinFlipping.h"
 #include "roms/romCONNECT4.h"
 #include "roms/romCrapsCamerlo.h"
 #include "roms/romDeflection.h"
 #include "roms/romDelayTimerTe.h"
 #include "roms/romDivisionTest.h"
 #include "roms/romFigures.h"
 #include "roms/romFilter.h"
 #include "roms/romFishie.h"
 #include "roms/romFramedMK1.h"
 #include "roms/romFramedMK2.h"
 #include "roms/romGUESS.h"
 #include "roms/romHIDDEN.h"
 #include "roms/romHiLo.h"
 #include "roms/romIBMLogo.h"
 #include "roms/romINVADERS.h"
 #include "roms/romJumpingXandO.h"
 #include "roms/romKALEID.h"
 #include "roms/romKeypadTest.h"
 #include "roms/romLanding.h"
 #include "roms/romLife.h"
 #include "roms/romLunarLander.h"
 #include "roms/romMastermindFo.h"
 #include "roms/romMAZE.h"
 #include "roms/romMERLIN.h"
 #include "roms/romMinimalgame.h"
 #include "roms/romMISSILE.h"
 #include "roms/romMostDangerou.h"
 #include "roms/romNim.h"
 #include "roms/romPaddles.h"
 #include "roms/romParticleDemo.h"
 #include "roms/romPONG.h"
 #include "roms/romPong1player.h"
 #include "roms/romPONG2.h"
 #include "roms/romPUZZLE.h"
 #include "roms/romRandomNumber.h"
 #include "roms/romReversi.h"
 #include "roms/romRocket_Launc.h"
 #include "roms/romRocket.h"
 #include "roms/romRushHour.h"
 #include "roms/romRussianRoule.h"
 #include "roms/romSequenceShoo.h"
 #include "roms/romShootingStar.h"
 #include "roms/romSierpinski.h"
 #include "roms/romSlide.h"
 #include "roms/romSoccer.h"
 #include "roms/romSpacefighter.h"
 #include "roms/romSpaceInterce.h"
 #include "roms/romSpookySpot.h"
 #include "roms/romSQRTTest.h"
 #include "roms/romSquash.h"
 #include "roms/romStars.h"
 #include "roms/romSubmarine.h"
 #include "roms/romSumFun.h"
 #include "roms/romSYZYGY.h"
 #include "roms/romTANK.h"
 #include "roms/romTapeworm.h"
 #include "roms/romTETRIS.h"
 #include "roms/romTICTAC.h"
 #include "roms/romTimebomb.h"
 #include "roms/romTrip8Demo.h"
 #include "roms/romTron.h"
 #include "roms/romUFO.h"
 #include "roms/romVBRIX.h"
 #include "roms/romVERS.h"
 #include "roms/romVerticalBrix.h"
 #include "roms/romWall.h"
 #include "roms/romWIPEOFF.h"
 #include "roms/romWormV4.h"
 #include "roms/romXMirror.h"
 #include "roms/romZeroDemo.h"
 #include "roms/romZeroPong.h"

 #define max_list_rom 88


 //roms
 //Titulos
 static const char * gb_list_rom_title[max_list_rom]={
  "15PUZZLE",
  "AdditionProb",
  "Airplane",
  "AnimalRace",
  "AstroDodge",
  "BiorhythmJef",
  "BLINKY",
  "BLITZ",
  "BMPViewerHel",
  "BowlingGooit",
  "BreakoutBrix",
  "BRIX",
  "Cave",
  "Chip8emulato",
  "Chip8Picture",
  "ClockProgram",
  "CoinFlipping",
  "CONNECT4",
  "CrapsCamerlo",
  "Deflection",
  "DelayTimerTe",
  "DivisionTest",
  "Figures",
  "Filter",
  "Fishie",
  "FramedMK1",
  "FramedMK2",
  "GUESS",
  "HIDDEN",
  "HiLo",
  "IBMLogo",
  "INVADERS",
  "JumpingXandO",
  "KALEID",
  "KeypadTest",
  "Landing",
  "Life",
  "LunarLander",
  "MastermindFo",
  "MAZE",
  "MERLIN",
  "Minimalgame",
  "MISSILE",
  "MostDangerou",
  "Nim",
  "Paddles",
  "ParticleDemo",
  "PONG",
  "Pong1player",
  "PONG2",
  "PUZZLE",
  "RandomNumber",
  "Reversi",
  "Rocket_Launc",
  "Rocket",
  "RushHour",
  "RussianRoule",
  "SequenceShoo",
  "ShootingStar",
  "Sierpinski",
  "Slide",
  "Soccer",
  "Spacefighter",
  "SpaceInterce",
  "SpookySpot",
  "SQRTTest",
  "Squash",
  "Stars",
  "Submarine",
  "SumFun",
  "SYZYGY",
  "TANK",
  "Tapeworm",
  "TETRIS",
  "TICTAC",
  "Timebomb",
  "Trip8Demo",
  "Tron",
  "UFO",
  "VBRIX",
  "VERS",
  "VerticalBrix",
  "Wall",
  "WIPEOFF",
  "WormV4",
  "XMirror",
  "ZeroDemo",
  "ZeroPong"
 };

 //Datos rom
 static const unsigned char * gb_list_rom_data[max_list_rom]={
  gb_rom_15PUZZLE,
  gb_rom_AdditionProb,
  gb_rom_Airplane,
  gb_rom_AnimalRace,
  gb_rom_AstroDodge,
  gb_rom_BiorhythmJef,
  gb_rom_BLINKY,
  gb_rom_BLITZ,
  gb_rom_BMPViewerHel,
  gb_rom_BowlingGooit,
  gb_rom_BreakoutBrix,
  gb_rom_BRIX,
  gb_rom_Cave,
  gb_rom_Chip8emulato,
  gb_rom_Chip8Picture,
  gb_rom_ClockProgram,
  gb_rom_CoinFlipping,
  gb_rom_CONNECT4,
  gb_rom_CrapsCamerlo,
  gb_rom_Deflection,
  gb_rom_DelayTimerTe,
  gb_rom_DivisionTest,
  gb_rom_Figures,
  gb_rom_Filter,
  gb_rom_Fishie,
  gb_rom_FramedMK1,
  gb_rom_FramedMK2,
  gb_rom_GUESS,
  gb_rom_HIDDEN,
  gb_rom_HiLo,
  gb_rom_IBMLogo,
  gb_rom_INVADERS,
  gb_rom_JumpingXandO,
  gb_rom_KALEID,
  gb_rom_KeypadTest,
  gb_rom_Landing,
  gb_rom_Life,
  gb_rom_LunarLander,
  gb_rom_MastermindFo,
  gb_rom_MAZE,
  gb_rom_MERLIN,
  gb_rom_Minimalgame,
  gb_rom_MISSILE,
  gb_rom_MostDangerou,
  gb_rom_Nim,
  gb_rom_Paddles,
  gb_rom_ParticleDemo,
  gb_rom_PONG,
  gb_rom_Pong1player,
  gb_rom_PONG2,
  gb_rom_PUZZLE,
  gb_rom_RandomNumber,
  gb_rom_Reversi,
  gb_rom_Rocket_Launc,
  gb_rom_Rocket,
  gb_rom_RushHour,
  gb_rom_RussianRoule,
  gb_rom_SequenceShoo,
  gb_rom_ShootingStar,
  gb_rom_Sierpinski,
  gb_rom_Slide,
  gb_rom_Soccer,
  gb_rom_Spacefighter,
  gb_rom_SpaceInterce,
  gb_rom_SpookySpot,
  gb_rom_SQRTTest,
  gb_rom_Squash,
  gb_rom_Stars,
  gb_rom_Submarine,
  gb_rom_SumFun,
  gb_rom_SYZYGY,
  gb_rom_TANK,
  gb_rom_Tapeworm,
  gb_rom_TETRIS,
  gb_rom_TICTAC,
  gb_rom_Timebomb,
  gb_rom_Trip8Demo,
  gb_rom_Tron,
  gb_rom_UFO,
  gb_rom_VBRIX,
  gb_rom_VERS,
  gb_rom_VerticalBrix,
  gb_rom_Wall,
  gb_rom_WIPEOFF,
  gb_rom_WormV4,
  gb_rom_XMirror,
  gb_rom_ZeroDemo,
  gb_rom_ZeroPong
 };

 //Tamanio en bytes
 static const int gb_list_rom_size[max_list_rom]={
  384,
  168,
  356,
  1194,
  1113,
  910,
  2356,
  391,
  304,
  1194,
  280,
  280,
  882,
  288,
  164,
  280,
  108,
  194,
  192,
  1024,
  58,
  371,
  290,
  198,
  160,
  176,
  176,
  148,
  850,
  170,
  132,
  1283,
  82,
  120,
  114,
  276,
  256,
  1792,
  292,
  34,
  345,
  85,
  180,
  1010,
  182,
  560,
  353,
  246,
  246,
  264,
  184,
  34,
  578,
  112,
  130,
  3582,
  156,
  324,
  204,
  521,
  388,
  334,
  1020,
  192,
  154,
  386,
  211,
  968,
  288,
  176,
  946,
  560,
  284,
  494,
  486,
  144,
  3203,
  382,
  224,
  507,
  230,
  507,
  229,
  206,
  677,
  106,
  144,
  184
 };

#endif
