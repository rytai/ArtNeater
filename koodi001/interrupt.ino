void timerISR(void *args){
  os_intr_lock();
  interrupt_test = true;

  if(operation_mode==1){
    //simpleRGB
  }
  else if(operation_mode==2){
    //joku demo
  }
  else if(operation_mode=0&&new_artnet_data){
    
  }
    os_intr_unlock();
}

