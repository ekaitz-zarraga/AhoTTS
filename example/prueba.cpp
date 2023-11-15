#include "src/htts.hpp"

int main (int argc, char* argv[]){


    HTTS *tts = new HTTS;
    tts->set("PthModel", "Pth1"); //not used but must be defined
    tts->set("Method", "HTS"); //HTS -> HMM-based method
    tts->set("Lang", "eu");
    char lang[] = "eu";
    char data_path[]="this";
    char dic_path[1024];
    sprintf(dic_path, "%s/dicts/eu_dicc", data_path); // TODO
    tts->set("HDicDBName",dic_path);

    if (!tts->create()) {
            delete tts;
            return 0;
    }


    char voice_path[1024];
    if (!strcmp(lang,"eu")){
            sprintf(voice_path, "%s/voices/aholab_eu_female/", data_path);// TODO Female Basque Voice
    }
    // SET THE VOICE PATH
    tts->set("voice_path", voice_path);
    tts->set("vp", "yes");

    // CAudioFile fout;
    // fout.open(output_file,"w", "SRate=16000.0 NChan=1 FFormat=Wav"); //Mono, 16kHz

    char str[] = "Putaseme halakoa";
    if(tts->input_multilingual(str, lang, data_path, FALSE)){ //FALSE => str contains the input text
        short *samples;
        int len=0;
        //PROCESS A SENTENCE FROM THE TEXT AND GET "len" samples
        while((len = tts->output_multilingual(lang, &samples)) != 0){
            //samples are stored in the audio file, but could also be directed to the soundcard
            // fout.setBlk(samples, len);
            free(samples); // Free the samples: they are allocated on the
                           // output_multilingual function!
        }
    }

    return 0;
}
