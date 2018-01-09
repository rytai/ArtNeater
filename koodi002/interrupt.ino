void timerISR(void *args){
  os_intr_lock();
  interrupt_test = true;

  if(operation_mode==1){
    //simpleRGB
    //Ladataan yksi väri
    //Ei tarvitse toistaa muuten kuin väriä vaihtaessa.
    if (simpleRGB_change){
      RGBtoLeds();
    }
  }
  else if(operation_mode==2){
    //joku demo
    //Animaatiota pykälä eteenpäin
  }
  else if(operation_mode=0&&new_artnet_data){
    //Artnet-datan lataus taulukosta
    ArtnetToLeds();
  }
    os_intr_unlock();
}

