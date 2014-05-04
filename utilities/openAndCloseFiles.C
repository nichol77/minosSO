


void openAndCloseFiles()
{

  const char *fileTypeTag[3]={"main","nue","tau"};

  char fileName[180];
  for(int fileType=0;fileType<3;fileType++) {
    for(int dmi=0;dmi<100;dmi++) {
      sprintf(fileName,"farPreds/run11/%s%d.root",fileTypeTag[fileType],dmi);
      TFile *fp = TFile::Open(fileName,"UPDATE");
      fp->Close();
    }
  }
}


