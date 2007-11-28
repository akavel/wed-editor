
/* =====[ CBNBIO.C ]=========================================================

   %DOCUMENT%

    ---------------------------------------------------------------------

    INTERNAL DOCUMENT.

    THIS DOCUMENTATION SHOULD BE USED TO GENERATE TEXT FOR THE MANUALS.

    Description:

            Crypto box PIER to PIER server. It allows several CBN
            boxes to be visible from the outside of the workstation on the
            local NETWORK.

            Now it comes in a DLL format.

    Note:   Most of the limitations are not effecting every day
            operations, but has to be noted by the users or programmers.

            The limitations come from the fact, that we have interrupt time
            processing to do with the real time functions. As such, I have
            tried to avoid MALLOC() call. This avoidance makes the server
            more stable. (extremly stable, in fact)
            The limitation comes in the flavor of fixed buffers.

            The limitations can be expanded by the defines:

                   MAX_BUFFER                   // buffer size
                   MAX_SERVER_LICENCE           // max number of licences

            If there is a strong need for dynamic expansion of
            limitations, it is feasable to implement.

            The current CBN limitations are as follows:

            MAX 1024 bytes can be processed at any one time.
            MAX 255 licences can be active  at any one time.
            MAX 65k appliction ID-s can be active at any one time.

   How it works:

            NETBIOS is an excellent protocol to make our Point to Point
            CBN fit almost any environment.
            The server listens for connections from the CBN clients, and
            serves requests. After the request is served, the CBN client
            requests close connection and the server listens for new
            connection.
            There is no ongoing (pending) connection to the CBN server
            after the transaction is complete.

            On an event, the main window (whish is hidden) gets a
            message. The message conveys a pointer to a buffer, that
            contains the request packet from the client.

            We execute all requests from that message, and send back
            the same buffer to the client with the results filled in.

   Access coordination:

             First come, first served. Requests are queued. The queued
             limits are configurable in NETBIOS. The factory default
             of NETBIOS is sufficient for PC networks.

   !DOCUMENT!

   Compiled:        MS-VC.

   Compiler opt:    See makefile.

   Revisions:

      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  04/25/96  Peter Glen    Initial version.
      0.00  05/15/98  Peter Glen    32 bit porting.

      REV     DATE           BY           DESCRIPTION
      ----  -----------     ----------  ----------------------------------
      2.01  13-Oct-1999     Peter Glen  Cleaned cummulative licences

   ======================================================================= */

/*
 * Original Functions:
 *
 *     WinMain()           - calls init function, processes message loop
 *     InitApplication()   - initializes window data and registers window
 *     InitInstance()      - saves instance handle and creates main window
 *     BiosWndProc()       - processes messages
 *     About()             - processes messages for "About" dialog box
 *
 * Original functions are grabbed from authentic Microsoft skeleton.
 *
 *    ADDED FUNCTIONS:
 *
 *     act_buffer          - Process recived info from client
 *     res_out             - Put results to output
 *     end_session         - Close conversation
 *     act_buffer          - Bo action encoded in buffer
 *
 */

#include "windows.h"              /* required for all Windows applications */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dos.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <conio.h>
#include <malloc.h>

#include "..\common\notepad.h"
#include "..\common\cbn_nb.h"
#include "..\common\cbnbio.h"

#define  EXPORT
#include "cbnbio_.h"
#include "lic_calc.h"

#include "interfce.h"

#pragma warning(disable: 4704)                      /* no optimzer warning */

extern HWND    hMainWnd;
extern unsigned short CalcFreeLic2(char *SCodeID, WORD appid);
extern void RepaintDialog();

/* -------- Defines: ----------------------------------------------------- */

//define BOX_NET_ERROR       0x14

#include "resourc2.h"

//
// Debug stuff
//

//define PG_DEBUG

//
// Config stuff
//

#define MAX_PORT 3

/* -------- Protos: ------------------------------------------------------ */

int CbNNReadMinl(unsigned short iPortNr, unsigned short iIdNr,
               unsigned char *pcSCodeId, unsigned char *pcDataIn);

/* -------- Data: -------------------------------------------------------- */

short   sMaxBoxLic = 0;
char    str2[64];

/* -------- Imports: ----------------------------------------------------- */

short  CB560_scan(
                        unsigned short iOpCode,
                        unsigned short iPortNr,
                        void  FAR *pcInData,
                        void  FAR *pcOutData,
                        unsigned short    iOutlen
                 );

/*
 * A Buffer from the client is handed to us, do CBN stuff:
 */

short     act_buffer(char *buff, NCB *ncb)

{
    short           loop1, lenn;
    short           slot = -1;
    short           done = FALSE;
    short           ret_val = 0;
    short           ret_val2 = 0;

    MARXNET_I_O     *in_ptr = (MARXNET_I_O  *)buff;
    LICENCE         *lic;
    char            min_count = 0;

    //HWND ServerHndl;

    #ifdef PG_DEBUG
    PrintToNotepad("CBNBIO: In act Buffer\r\n");
    #endif

    /*
     * Determine if textual command:
     *
     * This actually means that the CBN server can be administered
     * totally from the client side.
     *
     */

    if(!strcmp(buff, "hangup"))
        {
        //res_out("Remote hang up requested.\n");

        ret_val = NB_HANGUP;
        goto endd1;
        }

    /*
     * This command is not actually used. Implemented for greater
     * control over the server from the client side.
     */

    if(!strcmp(buff, "exit"))
        {
        res_out("Remote exit requested.\n");

        ret_val = NB_EXIT;
        goto endd1;
        }

    res_out("Request for ");

    /*
     * If we get here, we have serious work to do:
     *
     * a. Put some display output,
     * b. Switch decide what to do,
     * c. Execute request ...
     * d. Return data and code
     *
     */

    switch(in_ptr->iOpCode & 0xff)
        {
        //
        // The following switch is actually doing the
        // same as CBN opcodes.
        //

        case 0x1:           res_out("ID 1 "); break;
        case 0x2:           res_out("ID 2 "); break;
        case 0x3:           res_out("ID 3 "); break;
        case 0x4:           res_out("ID 4 "); break;
        case 0x5:           res_out("ID 5 "); break;
        case 0x6:           res_out("ID 6 "); break;
        case 0x7:           res_out("ID 7 "); break;
        case 0x8:           res_out("ID 8 "); break;

        case 0x10:          res_out("serial number "); break;
        case 0x11:          res_out("encrypt "); break;
        case 0x12:          res_out("decrypt "); break;
        case 0x13:          res_out("box ready "); break;

        case 0x14:          res_out("read RAM1 "); break;
        case 0x15:          res_out("read RAM2 "); break;
        case 0x16:          res_out("write RAM1 "); break;
        case 0x17:          res_out("write RAM2 "); break;
        case 0x18:          res_out("increment RAM1 "); break;
        case 0x20:          res_out("increment RAM2 "); break;
        case 0x19:          res_out("decrement RAM1 "); break;
        case 0x21:          res_out("decrement RAM2 "); break;
        case 0x29:          res_out("IDEA "); break;

        case LIC_INCREMENT: res_out("LICENCE Increment "); break;
        case LIC_DECREMENT: res_out("LICENCE Decrement"); break;
        case LIC_CMP      : res_out("LICENCE compare "); break;
        case LIC_STAT     : res_out("LICENCE stat "); break;
        case LIC_SER_MAX  : res_out("LICENCE server max "); break;
        case LIC_MAX      : res_out("LICENCE max "); break;
        case LIC_READRAM  : res_out("READ LICENCE RAM "); break;
        case LIC_WRITERAM : res_out("WRITE LICENCE RAM "); break;

        default:            res_out("ERROR: Bad opcode transmitted "); break;
        }

    if(!enabled)
        {
        res_out("Server disabled, request denied.\n");
        in_ptr->ret_val = CBN_ERR_NETWORK;
        goto endd;
        }

    //
    // The following switches are executing LICENCE functions:
    //

    switch(in_ptr->iOpCode & 0xff)
        {
        short   count = 0;

        case LIC_INCREMENT:
            {
            lic = (LICENCE *) in_ptr->firstbyte;

            #ifdef PG_DEBUG
            PrintToNotepad("CBNBIO: Registering card: '%x' '%s' '%d'\r\n",
                                        lic->card, lic->name, lic->app);
            #endif
            /*
             * Ask CBN about the licence:
             */
            in_ptr->ret_val = CbNNReadMinl(1, 1, in_ptr->input, &min_count);

            if(in_ptr->ret_val)
                goto endd;

            WALK_LICENCES(loop1)            // Walk the available slot space
                {
                /*
                 * Empty slot ?
                 */
                if( (lic_ram[loop1].card == -1) && (slot == -1))
                    {
                    // Remember slot space:
                    slot = loop1;
                    }
                   /*
                    * Is this card registered already?
                    */
                if( (lic->card == lic_ram[loop1].card) &&
                    (lic->app  == lic_ram[loop1].app)
                  )
                    {
                    /*
                     * We deliver the result in the network card field.
                     * Dirty dirty, but it is an unused field in this call.
                     */
                    lic->card = CBN_NB_ALREADY_RGISTRD;

                    /*
                     * User may want this licence as timeout licence,
                     * refresh timeout.
                     */
                    lic_ram[loop1].timeout = lic->timeout;

                    #ifdef PG_DEBUG
                    PrintToNotepad("CBNBIO: station already registered.\r\n");
                    #endif

                    done = TRUE;                       // signal done state
                    break;
                    }
                }

            if(lic->card == CBN_NB_ALREADY_RGISTRD)
                goto endd;

            /*
             * Ask CBN about the Licences:
             */
            if(CalcFreeLic2(in_ptr->input, lic->app) == 0)
                {
                #ifdef PG_DEBUG
                PrintToNotepad("CBNBIO: sMaxBox: %d, Min: %d\r\n",
                                                    sMaxBoxLic, min_count);
                #endif

                lic->card = CBN_NB_NO_LICENSE_AVAIL;
                in_ptr->ret_val = SUCCESS;
                goto endd;
                }
              #ifdef PG_DEBUG
              PrintToNotepad("CBNBIO: In licence increment.\r\n");
              #endif

              /*
               * Register us into this session:
               */

              if(!done)
              {
                if(slot == -1)                  // no more available slots
                {
                  /*
                   * We deliver the result in the network card field.
                   * Dirty dirty, but it is an unused field in this call.
                   */
                  lic->card = CBN_NB_NO_LICENSE_AVAIL;
                  in_ptr->ret_val = SUCCESS;
                  goto endd;
                }

             /*
              * Finaly, we register it:
              */
              memcpy(&lic_ram[slot], lic, sizeof(LICENCE));
              memcpy(&(lic_ram[slot].SCodeID), in_ptr->input, 3);

              //sMaxBoxLic = CalcAllFreeLic();
              memcpy(lic->SCodeID, lic_ram[slot].SCodeID, 3);

              #ifdef PG_DEBUG
              PrintToNotepad("CBNBIO: Registered station.\r\n" );
              #endif

              lic->card =  CBN_NB_NEW_REGISTRATION;
              in_ptr->ret_val = SUCCESS;

             // Report on success:

             count = 0;
             WALK_LICENCES(loop1)            // Walk the available slot space
                {
                if(lic_ram[loop1].card != -1)      // found occupied entry
                    {
                    // if(lic_ram[loop1].app == lic->app)        // found app
                        count++;
                    }
                }

             #ifdef PG_DEBUG
             PrintToNotepad("CBNBIO: lic mem dump\r\n");
             DumpToNotepad((void*)lic_ram, MAX_SERVER_LICENCE * sizeof(LICENCE));
             PrintToNotepad("CBNBIO: end mem dump\r\n");
             #endif

             sprintf(str2, "Registered %d of %d licences", count, min_count);
             SetWindowText(hMainWnd, str2);
             RepaintDialog();
             }
         }
         break;

        case LIC_DECREMENT:

            lic = (LICENCE *) in_ptr->firstbyte;

            #ifdef PG_DEBUG
            PrintToNotepad("CBNBIO: Unregistering card: %x %s\r\n",
                                          lic->card, lic->name, lic->app);
            #endif


            /*
             * Ask CBN about the CBN:
             */
            in_ptr->ret_val = CbNNReadMinl(1, 1, in_ptr->input, &min_count);

            if(in_ptr->ret_val)
                {
                #ifdef PG_DEBUG
                PrintToNotepad("CBNBIO: cannot get lic count\r\n", lic);
                #endif

                goto endd;
                }

            WALK_LICENCES(loop1)            // Walk the available slot space
                {
                //if(lic->card == lic_ram[loop1].card &&
                //    lic->app == lic_ram[loop1].app &&
                //    (!memcmp(lic_ram[loop1].SCodeID, in_ptr->input, 3))
                //  )

                if(lic->card == lic_ram[loop1].card &&
                    lic->app == lic_ram[loop1].app )
                    {

                    //
                    // Found this card, kill it:
                    //
                    //if ( min_count != 255 )
                    //    {
                    //    sMaxBoxLic++;
                    //    }
                    //

                    //
                    //lic_ram[loop1].card = 0;
                    //sMaxBoxLic = CalcAllFreeLic();
                    //lic_ram[loop1].card = lic->card;
                    //
                    //memcpy(lic->SCodeID, lic_ram[loop1].SCodeID, 3);


                    // Erase this one from memory:

                    memset(&lic_ram[loop1], 0xff, sizeof(LICENCE));

                    lic->card = CBN_NB_DECREMENTED_LIC;
                    done = TRUE;

                    #ifdef PG_DEBUG
                    PrintToNotepad("CBNBIO: station de-registered.\r\n");
                    #endif

                    //
                    // We do not break here, as we remove all occurrances.
                    //
                    }

                }
            if(!done)                      // we have not found this entry
                {
                //
                // was not registered, tell the user
                //
                lic->card = CBN_NB_WAS_NOT_RGISTRD;

                #ifdef PG_DEBUG
                PrintToNotepad(
                 "CBNBIO: Non registered station tried to un-register.\r\n");
                #endif
                }

             // Report on success:

             count = 0;
             WALK_LICENCES(loop1)            // Walk the available slot space
                {
                if(lic_ram[loop1].card != -1)    // found occupied entry
                    {
                    //if(lic_ram[loop1].app == lic->app)        // found app
                        count++;
                    }
                }

                #ifdef PG_DEBUG
                PrintToNotepad("CBNBIO: lic mem dump\r\n");
                DumpToNotepad((void*)lic_ram, MAX_SERVER_LICENCE * sizeof(LICENCE));
                PrintToNotepad("CBNBIO: end mem dump\r\n");
                #endif

             sprintf(str2, "Registered %d of %d licences", count, min_count);
             SetWindowText(hMainWnd, str2);
             RepaintDialog();

            in_ptr->ret_val = SUCCESS;
            break;

        case LIC_CMP      :
            {
            //short   count = 0;
            //char    min_count = 0;

            lic = (LICENCE *) in_ptr->firstbyte;
            lic->card = CMP_ERR   ;

            /*
             * Ask CBN about the licence:
             */
            in_ptr->ret_val = CbNNReadMinl(1, 1, in_ptr->input, &min_count);

            if(in_ptr->ret_val)
                goto endd;

            /*
             * Ask SERVER about the registered licences:
             */
            WALK_LICENCES(loop1)            // Walk the available slot space
                {
                if(lic_ram[loop1].card != -1)    // found occupied entry
                    {
                    if(lic_ram[loop1].app == lic->app)        // found app
                        count++;
                    }
                }

            #ifdef PG_DEBUG
            PrintToNotepad("CBNBIO: Licence: SERVER: %d CBN %d\r\n",
                                                        count, min_count);
            #endif

            if(count < min_count)
                lic->card = CMP_OK;
            else
                lic->card = CMP_FULL;

            in_ptr->ret_val = SUCCESS;
            }
            break;

        case LIC_STAT     :
            {
            short count = 0;
            lic = (LICENCE *) in_ptr->firstbyte;

            WALK_LICENCES(loop1)            // Walk the available slot space
                {
                if(lic_ram[loop1].card != -1)    // found occupied entry
                    {
                    if(lic_ram[loop1].app == lic->app)        // found app
                        count++;
                    }
                }
            /*
             * We deliver the count in the network card field.
             * Dirty dirty, but it is an unused field in this call.
             */
            lic->card = (long)count;
            in_ptr->ret_val = SUCCESS;
            }
            break;

        case LIC_MAX      :
            {

            /*
             * Ask CBN about the licence:
             */
            in_ptr->ret_val = CbNNReadMinl(1, 1, in_ptr->input, &min_count);

            #ifdef PG_DEBUG
            PrintToNotepad("CBNBIO: readmin: %d\r\n", min_count);
            #endif

            *((long*)in_ptr->firstbyte) = (long)min_count;
            }
            break;

        case LIC_SET_LIMIT    :
            *((long*)in_ptr->firstbyte) = 1;
            in_ptr->ret_val = SUCCESS;
            break;

        case LIC_SER_MAX      :
            *((long*)in_ptr->firstbyte) = MAX_SERVER_LICENCE;
            in_ptr->ret_val = SUCCESS;
            break;

        case LIC_READRAM  :
            lenn = min((sizeof(lic_ram) - in_ptr->iPortNr), in_ptr->len);
            memcpy(in_ptr->firstbyte, &lic_ram[in_ptr->iPortNr], lenn);
            in_ptr->ret_val = SUCCESS;
            break;

        case LIC_WRITERAM :
            lenn = min((sizeof(lic_ram) - in_ptr->iPortNr), in_ptr->len);
            memcpy(&lic_ram[in_ptr->iPortNr], in_ptr->firstbyte, lenn);
            in_ptr->ret_val = SUCCESS;
            break;

        // -------------------------------------------------------------

        case 0x1:
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:

        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x20:
        case 0x19:
        case 0x21:
        case 0x29:
            {
            short box_ret_val;
            short access = 0;

            res_out("on port: %d ", in_ptr->iPortNr);

            //
            // If it is not a box ready, we check access dependent on logon
            //
            if((in_ptr->iOpCode & 0xff) != 0x13)
                {
                //DWORD card = *((DWORD*)(&in_ptr->input[8]));
                // fix:  card id in field

                DWORD card = in_ptr->card_id;


                #ifdef PG_DEBUG
                PrintToNotepad("CBNBIO: Netcard ID CBN op: %x\r\n", card);
                #endif

                /*
                 * Check if it is a logged in client
                 */

                WALK_LICENCES(loop1)        // Walk the available slot space
                    {
                    /*
                     * Is this card registered already?
                     */
                    if(card == lic_ram[loop1].card)
                        {
                        access = 1;
                        break;
                        }
                    }
                if(!access)
                    {
                    res_out("access denied ", in_ptr->iPortNr);

                    box_ret_val = CBN_ERR_ACCESS_DENY;
                    in_ptr->ret_val = box_ret_val;
                    goto endd;
                    }
                }
            in_ptr->len = ncb->ncb_length - offsetof(MARXNET_I_O, firstbyte);
            /*
             * Call the BOXIO:
             */
            box_ret_val = CB560_scan(
                                in_ptr->iOpCode,
                                in_ptr->iPortNr,
                                in_ptr->input,
                                in_ptr->firstbyte,
                                in_ptr->len
                               );

            /*
             * Return values in the output buffer pool:
             */

            in_ptr->ret_val = box_ret_val;
            in_ptr->len = ncb->ncb_length - offsetof(MARXNET_I_O, firstbyte);
            }
            break;

        default:
           ret_val = NB_HANGUP;
           break;

       }
    endd:
       res_out("Returned: %d\n", in_ptr->ret_val);

    endd1:
    return(ret_val);
}

int CbNNReadMinl(unsigned short iPortNr, unsigned short iIdNr,
               unsigned char *pcSCodeId, unsigned char *pcDataIn)
{
    unsigned char cInField[4];
    unsigned short  iOpCode;
    int  iRetValue;

    *pcDataIn = 255;
    //return(0);

    cInField[0] = (unsigned char) (iIdNr & 0xff);
    cInField[1] = *(pcSCodeId+2);
    cInField[2] = *(pcSCodeId+1);
    cInField[3] = *pcSCodeId;

    iOpCode = 0x52;

    iRetValue = CB560_scan(iOpCode, iPortNr, cInField, pcDataIn, 1);

    return(iRetValue);
}

/*
 * Scan pre-fix for CB560
 *
 * The assembler is so dirty, we pre-scan for port access.
 *
 */

short  CB560_scan(
                        unsigned short iOpCode,
                        unsigned short iPortNr,
                        void  FAR *pcInData,
                        void  FAR *pcOutData,
                        unsigned short    iOutlen
                 )

{
    short       ret_val = 0, ret_val2 = 0, solid = 0;

    char *InData =  (char*)pcInData;
    char *OutData = (char*)pcOutData;


    if(iPortNr >= 10)
        {
        solid = 1;                      // no auto search
        iPortNr -= 10;
        }
    iPortNr = min(iPortNr, 3);          // safety port number limit

    #ifdef PG_DEBUG
    PrintToNotepad(
    "CBNBIO: cb560_scan opcode:%d  port:%d in:%02x%02x%02x%02x \
     out:%02x%02x%02x%02x len: %d\r\n",
                        iOpCode, iPortNr,
                        InData[0],
                        InData[1],
                        InData[2],
                        InData[3],
                        OutData[0],
                        OutData[1],
                        OutData[2],
                        OutData[3],
                        iOutlen);
    #endif

    /*
     * See if we have got a LOCAL crypto box, do action:
     */

    if(solid)
        {
        ret_val = cb560_ext(iOpCode, iPortNr,
                      (unsigned char FAR *)pcInData,
                      (unsigned char FAR *)pcOutData,
                      iOutlen);
        }
    else
        {
        short port, ports[2 * (MAX_PORT + 1)];

        ret_val = -1;

        /*
         * Make port scan sceme:
         */
        for(port = 0; port < MAX_PORT; port++)
            {
            ports[port] = port+1;
            ports[port + MAX_PORT ] = port+1;
            }

        /*
         * Scan ports as in spec:
         */
        for(port = 0; port < MAX_PORT; port++)
            {
            #ifdef PG_DEBUG
            //PrintToNotepad("CBNBIO: Scanning port: %d\r\n",
            //                                ports[port + iPortNr-1]);
            #endif

            ret_val2 = cb560_ext(iOpCode, ports[port + iPortNr-1],
                      (unsigned char FAR *)pcInData,
                      (unsigned char FAR *)pcOutData,
                      iOutlen);

            /*
             * The box responded, we need search no further:
             */
            if(!ret_val2)
                {
                ret_val = ret_val2;
                break;
                }
            if(ret_val2 != -1)
                {
                ret_val = ret_val2;
                }
            }
        }

    #ifdef PG_DEBUG
    //PrintToNotepad(
    //"CBNBIO: cb560_scan end opcode:%d  port:%d in:%02x%02x%02x%02x \
    // out:%02x%02x%02x%02x len: %d\r\n",
    //                    iOpCode, iPortNr,
    //                    InData[0],
    //                    InData[1],
    //                    InData[2],
    //                    InData[3],
    //                    OutData[0],
    //                    OutData[1],
    //                    OutData[2],
    //                    OutData[3],
    //                    iOutlen);
    #endif

    return(ret_val);
}

/* EOF */
