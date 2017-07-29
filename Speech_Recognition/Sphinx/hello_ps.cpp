#include <pocketsphinx.h>

int
main(int argc, char *argv[])
{
    ps_decoder_t *ps;
    cmd_ln_t *config;
    FILE *fh;
    char const *hyp, *uttid;
    int16 buf[512];
    int rv;
    int32 score;

//create config settings for future decoder
    config = cmd_ln_init(NULL, ps_args(), TRUE, //null - new config settings (not updating old ones), ps_args() - gives array of definition arguments from cmd_ln_init(), true - strict - will fail on duplicate or unknown arguments.
                 "-hmm", MODELDIR "/en-us/en-us",
                 "-lm", MODELDIR "/en-us/en-us.lm.bin", //language model to use
                 "-dict", MODELDIR "/en-us/cmudict-en-us.dict", //dictionary to use
                 NULL);
    if (config == NULL) { //if config is null we have bad configuration (maybe it couldnt find the dictionary or something)
        fprintf(stderr, "Failed to create config object, see log for details\n");
        return -1;
    }
    
    ps = ps_init(config); //creates the decoder (which is ps) uses the config settings we set before.
    if (ps == NULL) {
        fprintf(stderr, "Failed to create recognizer, see log for details\n");
        return -1;
    }

    fh = fopen("goforward.raw", "rb"); //opens the file for editing. rb- reading non-text files (as opposed to r which is for text files)
    if (fh == NULL) {
        fprintf(stderr, "Unable to open input file goforward.raw\n");
        return -1;
    }

    rv = ps_start_utt(ps); //starts utterance processing. rv=0 if initialized correctly, otherwise rv<0.
    
    while (!feof(fh)) { //feof() checks for end of file - the while wil lrun until file ends.
        size_t nsamp;
        nsamp = fread(buf, 2, 512, fh); //buf is an array. fread reads the stream from the file fh and inserts it to buf. 2- the size in bytes of each element to be read. 512 - the amount of elements to be read. nsamp gets the value of the amount of elements succesfully read - should be equal to  512 unless end of file was reached or there was an error.
        rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE); //decode raw data using the decoder ps, the data collected in buf. first FALSE - do not start feature extraction yet. secound FALSE - if it were a number it would signify a block of data with a full utterance, which could help accuracy, false means we don't know of such a block. rv recieves number of frames of data searched, if rv<0 we have an error
    }
    
    rv = ps_end_utt(ps); //end utterance processing, returns 0 for success, <0 for error
    hyp = ps_get_hyp(ps, &score); //get hypothesis string (text of the voice file??) and paths score(???). hyp gets the text of the hypothesis string.
    printf("Recognized: %s\n", hyp);

    fclose(fh); //closes the file fh
    ps_free(ps); //finallize the decoder - releases all the resources associated with the decoder including language models and grammers
    cmd_ln_free_r(config); //release command line argument set and all associated strings.
    
    return 0;
}
