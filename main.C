#include <unistd.h>
#include <iostream>

#include "byutr.h"
#include "pagetable.h"
#include "map.h"

using namespace std;

char* outputFileName;
char* inputTraceFileName;
int* entryCountSizes;
int entryCountIndex = 0;
bool showLogToPhysTranslation = false;
int numMemoryRefs = -1;

void parseArguments(int argc, char **argv) {
  int option;
  int flagCount = 0;
  entryCountSizes = new int[argc];
  while ( (option = getopt(argc, argv, "n:p:t")) != -1) {
    switch (option) {
      case 'n': /* Number of addresses to process */
      numMemoryRefs = atoi(optarg);
      flagCount++;
      // optarg will contain the string following -n
      // Process appropriately (e.g. convert to integer atoi(optarg))
      break;
      case 'p': /* produce map of pages */
      // optarg contains name of page file…
      outputFileName = optarg;
      flagCount++;
      break;
      case 't': /* Show address translation */
      // No argument this time, just set a flag
      showLogToPhysTranslation = true;
      break;
      default:
      // print something about the usage and die…
      //exit(BADFLAG); // BADFLAG is an error # defined in a header
      cout << "default called" << endl;
      break;
    }
 //idx = optind;
  }
  cout << "num of args: " << argc << endl;
  
  int flagTotalCounter = flagCount*2 + (int)showLogToPhysTranslation;
  //int flagOffset = 
  //int intCheck;
  if(argc > 1) {
    for(int i = flagTotalCounter+1; i < argc; i++) {
      if (isdigit(argv[i][0])) {
        int argAsInt = atoi(argv[i]);
        entryCountSizes[entryCountIndex] = argAsInt;
        cout << "digit found: " << argAsInt << endl;
        entryCountIndex++;
      } else if(sizeof(argv[i]) > 2 && isalpha(argv[i][0])) {
        inputTraceFileName = argv[i];
        cout << "trace file found: " << argv[i] << endl;

      }
    }
  }
}


/*
 * If you are using this program on a big-endian machine (something
 * other than an Intel PC or equivalent) the unsigned longs will need
 * to be converted from little-endian to big-endian.
 */
uint32_t swap_endian(uint32_t num)
{
  return(((num << 24) & 0xff000000) | ((num << 8) & 0x00ff0000) | 
  ((num >> 8) & 0x0000ff00) | ((num >> 24) & 0x000000ff) );
}

/* determine if system is big- or little- endian */
ENDIAN endian()
{
  /* Allocate a 32 bit character array and pointer which will be used
   * to manipulate it.
   */
  uint32_t *a;
  unsigned char p[4];
  
  a = (uint32_t *) p;  /* Let a point to the character array */
  *a = 0x12345678; /* Store a known bit pattern to the array */
  /* Check the first byte.  If it contains the high order bits,
   * it is big-endian, otherwise little-endian.
   */
  if(*p == 0x12)
    return BIG;
  else
    return LITTLE;
}

/* int NextAddress(FILE *trace_file, p2AddrTr *Addr)
 * Fetch the next address from the trace.
 *
 * trace_file must be a file handle to an trace file opened
 * with fopen. User provides a pointer to an address structure.
 *
 * Populates the Addr structure and returns non-zero if successful.
 */
int NextAddress(FILE *trace_file, p2AddrTr *addr_ptr) {

  int readN;	/* number of records stored */ 
  static ENDIAN byte_order = UNKNOWN;	/* don't know machine format */

  if (byte_order == UNKNOWN) {
    /* First invocation.  Determine if this is a litte- or
     * big- endian machine so that we can convert bit patterns
     * if needed that are stored in little-endian format
     */
    byte_order = endian();
  }

  /* Read the next address record. */
  readN = fread(addr_ptr, sizeof(p2AddrTr), 1, trace_file);

  if (readN) {
    
    if (byte_order == BIG) {
      /* records stored in little endian format, convert */
      addr_ptr->addr = swap_endian(addr_ptr->addr);
      addr_ptr->time = swap_endian(addr_ptr->time);
    }
  }

  return readN;    
}


/* void AddressDecoder(p2AddrTr *addr_ptr, FILE *out)
 * Decode a Pentium II BYU address and print to the specified
 * file handle (opened by fopen in write mode)
 */
void AddressDecoder(p2AddrTr *addr_ptr, FILE *out) {
  
  fprintf(out, "%08lx ", addr_ptr->addr);	/* address */
  /* what type of address request */
  switch (addr_ptr->reqtype) {
    case FETCH:
      fprintf(out, "FETCH\t\t");
      break;
    case MEMREAD:
      fprintf(out, "MEMREAD\t");
      break;
    case MEMREADINV:
      fprintf(out, "MEMREADINV\t");
      break;
    case MEMWRITE:
      fprintf(out, "MEMWRITE\t");
      break;
    case IOREAD:
      fprintf(out, "IOREAD\t\t");
      break;
    case IOWRITE:
      fprintf(out, "IOWRITE\t");
      break;
    case DEFERREPLY:
      fprintf(out, "DEFERREPLY\t");
      break;
    case INTA:
      fprintf(out, "INTA\t\t");
      break;
    case CNTRLAGNTRES:
      fprintf(out, "CNTRLAGNTRES\t");
      break;
    case BRTRACEREC:
      fprintf(out, "BRTRACEREC\t");
      break;
    case SHUTDOWN:
      fprintf(out, "SHUTDOWN\t");
      break;
    case FLUSH:
      fprintf(out, "FLUSH\t\t");
      break;
    case HALT:
      fprintf(out, "HALT\t\t");
      break;
    case SYNC:
      fprintf(out, "SYNC\t\t");
      break;
    case FLUSHACK:
      fprintf(out, "FLUSHACK\t");
      break;
    case STOPCLKACK:
      fprintf(out, "STOPCLKAK\t");
      break;
    case SMIACK:
      fprintf(out, "SMIACK\t\t");
      break;
  }
  /* print remaining attributes:
     bytes accessed
     other tattributes
     process
     timestamp
  */
  fprintf(out, "%2d\t%02x\t%1d\t%08lx\n", addr_ptr->size, addr_ptr->attr,
	  addr_ptr->proc, addr_ptr->time);
}

int main(int argc, char **argv){
  parseArguments(argc, argv);


  PAGETABLE *p = new PAGETABLE(entryCountIndex, entryCountSizes);
    //cout << "last-1" << endl;

  //p->RootNodePtr->callp();
  // p->p();
  //   cout << "last-2" << endl;

  // cout << p->getOffset(0x12345678, 2) << endl;
  // p->PageInsert(0x12345678, 0x00000003);
  // MAP *m = p->PageLookup(0x12325679);
  // cout << "******" << endl;
  // bool b = false;
  // if(m){
  //   b = true;
  // }
  // cout << b << endl;

  FILE* ifp; 
  unsigned long i = 0;  /* instructions processed */
  p2AddrTr trace;	/* traced address */

/*
  // Creates a file "demo_file" 
  // with file acccess as write-plus mode 
  ifp = fopen(inputTraceFileName, "w+"); 

  NextAddress(demo, );
  // closes the file pointed by demo 
  fclose(demo); 
*/

  /* attempt to open trace file */
  if ((ifp = fopen(inputTraceFileName,"rb")) == NULL) {
    fprintf(stderr,"cannot open %s for reading\n",inputTraceFileName);
    exit(1);
  }
	
  int processCount = 0;
  unsigned int FrameCount = 0;
  while (!feof(ifp)) {
    if(numMemoryRefs != -1 && processCount > numMemoryRefs){
      break;
    }
    /* get next address and process */
    if (NextAddress(ifp, &trace)) {
      //AddressDecoder(&trace, stdout); //** use this later

      MAP *map = p->PageLookup(trace.addr);
      if(!map){
        //cout << trace.addr << endl;
        p->PageInsert(trace.addr, FrameCount);
        FrameCount++;
      }
      processCount++;

      i++;
      if ((i % 100000) == 0)
	      fprintf(stderr,"%dK samples processed\r", i/100000);
    }
  }

  p->printTable();	



  /* clean up and return success */
  fclose(ifp);
}
