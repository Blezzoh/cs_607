#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char* argv[]) {
    if (argc<2) {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }
    
    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);
    
    
    /* ================================ */
    /* START STUDENT MODIFIABLE SECTION */
    /* ================================ */
    
    // initializations
    PNMreader reader((char*) "../images/tux.pnm");
    Shrinker sr;
    LRCombine lr;
    
    // LRconcat -- SHOULD THROW AN ERROR (different dimensions)
                                        // (yes, it's boring)
    sr.SetInput(reader.GetOutput());
    lr.SetInput(reader.GetOutput());
    lr.SetInput2(sr.GetOutput());
    
    // "finalImage" is the image at the bottom of the pipeline
    Image* finalImage = lr.GetOutput();
    
    /* ================================ */
    /*  END STUDENT MODIFIABLE SECTION  */
    /* ================================ */
    
    
    try {
        finalImage->Update();
    }
    catch (DataFlowException&) {
        ofstream ofile("my_exception");
        if (ofile.fail()) {
            cerr << "Something is wrong ... can't open my_exception"
            << " for opening" << endl;
            exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }
    
    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");
    
    if (argc==3) {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write((char*) "3H.pnm");
    }
    Logger::Finalize();
}
