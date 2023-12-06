Minim minim;
AudioPlayer player;
String soundFileName = "sound.mp3";

void soundSetup() {
  minim = new Minim(this);
  player = minim.loadFile(soundFileName);
  player.loop();
  player.play();
  player.mute();
}
