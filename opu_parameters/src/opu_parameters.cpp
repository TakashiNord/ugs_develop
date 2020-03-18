//////////////////////////////////////////////////////////////////////////////
//
//  cam.cpp
//
//  Description:
//      Contains Unigraphics entry points for the application.
//
//////////////////////////////////////////////////////////////////////////////

//  Include files
#include <uf.h>
#include <uf_exit.h>
#include <uf_ui.h>

#include <uf_obj.h>
#include <uf_ui_ont.h>
#include <uf_oper.h>
#include <uf_part.h>
#include <uf_param.h>


#if ! defined ( __hp9000s800 ) && ! defined ( __sgi ) && ! defined ( __sun )
# include <strstream>
  using std::ostrstream;
  using std::endl;
  using std::ends;
#else
# include <strstream.h>
#endif
#include <iostream.h>

#include "opu_parameters.h"


#define UF_CALL(X) (report( __FILE__, __LINE__, #X, (X)))

static int report( char *file, int line, char *call, int irc)
{
  if (irc)
  {
     char    messg[133];
     printf("%s, line %d:  %s\n", file, line, call);
     (UF_get_fail_message(irc, messg)) ?
       printf("    returned a %d\n", irc) :
       printf("    returned error %d:  %s\n", irc, messg);
  }
  return(irc);
}

int opu_parameters();

//----------------------------------------------------------------------------
//  Activation Methods
//----------------------------------------------------------------------------

//  Explicit Activation
//      This entry point is used to activate the application explicitly, as in
//      "File->Execute UG/Open->User Function..."
extern "C" DllExport void ufusr( char *parm, int *returnCode, int rlen )
{
    /* Initialize the API environment */
    int errorCode = UF_initialize();

    if ( 0 == errorCode )
    {
        /* TODO: Add your application code here */
        opu_parameters();

        /* Terminate the API environment */
        errorCode = UF_terminate();
    }

    /* Print out any error messages */
    PrintErrorMessage( errorCode );
}

//----------------------------------------------------------------------------
//  Utilities
//----------------------------------------------------------------------------

// Unload Handler
//     This function specifies when to unload your application from Unigraphics.
//     If your application registers a callback (from a MenuScript item or a
//     User Defined Object for example), this function MUST return
//     "UF_UNLOAD_UG_TERMINATE".
extern "C" int ufusr_ask_unload( void )
{
     /* unload immediately after application exits*/
    return ( UF_UNLOAD_IMMEDIATELY );

     /*via the unload selection dialog... */
     //return ( UF_UNLOAD_SEL_DIALOG );
     /*when UG terminates...              */
     //return ( UF_UNLOAD_UG_TERMINATE );
}

/* PrintErrorMessage
**
**     Prints error messages to standard error and the Unigraphics status
**     line. */
static void PrintErrorMessage( int errorCode )
{
    if ( 0 != errorCode )
    {
        /* Retrieve the associated error message */
        char message[133];
        UF_get_fail_message( errorCode, message );

        /* Print out the message */
        UF_UI_set_status( message );

        fprintf( stderr, "%s\n", message );
    }
}


/*****************************************************************************************/

int opu_parameters()
{
/*  Variable Declarations */
    char str[133];
    char menu[14][38] ;
    int response ;

    tag_t prg = NULL_TAG;
    int   i , count = 0 ;
    int   obj_count = 0;
    tag_t *tags = NULL ;
    char  prog_name[UF_OPER_MAX_NAME_LEN+1];
    int type, subtype ;

    logical rsp;
    int j;
    int *indices_param; int count_param;

 /************************************************************************/

    int module_id;
    UF_ask_application_module(&module_id);
    if (UF_APP_CAM!=module_id) {
       // UF_APP_GATEWAY UF_APP_CAM UF_APP_MODELING UF_APP_NONE
       uc1601("Запуск DLL - производится из модуля обработки\n.",1);
       return (-1);
    }

    /* Ask displayed part tag */
    if (NULL_TAG==UF_PART_ask_display_part()) {
      uc1601("Cam-часть не активна.....\n программа прервана.",1);
      return (-2);
    }

 /************************************************************************/
  printf("\n\n\nopu_parameters()\n\n");

  strcpy(&menu[0][0], "Read Param from opers\0");
  strcpy(&menu[1][0], "Help\0");

  response=3;
  while (response != 1 && response != 2  && response != 19 )
  {

   response = uc1603("Select operations for List to create - Back or Cancel to terminate or finish.",1,menu, 1+1);

   if (response >= 3 || response < 19 )
   {
       switch (response)
       {
          case 5 :

      /********************************************************************************/
      /* Get the number of selected operation objects. */
      if (obj_count>0) { obj_count=0 ; UF_free(tags); }
      UF_CALL( UF_UI_ONT_ask_selected_nodes(&obj_count, &tags) );
      if (obj_count<=0) { uc1601("Не выбрано операций!\n..",1); break ; }

      UF_UI_toggle_stoplight(1);

      for(i=0,count=0;i<obj_count;i++)
      {
         prg = tags[i]; // идентификатор объекта

         UF_CALL( UF_OBJ_ask_type_and_subtype (prg, &type, &subtype ) );
         if (type!=UF_machining_operation_type) { continue ; }

         prog_name[0]='\0';
         //UF_OBJ_ask_name(prg, prog_name);// спросим имя обьекта
         UF_OPER_ask_name_from_tag(prg, prog_name);

         /*******************************************************/
         count_param=0;
         UF_PARAM_ask_required_params(prg,&count_param,&indices_param);
         
         UF_UI_open_listing_window();
         str[0]='\0'; sprintf(str,"\n %s (tag=%o) count_param=%d\n",prog_name,prg,count_param);
         UF_UI_write_listing_window(str);         
         for(j=0;j<count_param;j++)
         {
         	str[0]='\0';	
         	//sprintf(str,"\n\t%d)  %d",j,indices_param[j]);
         	sprintf(str,"\n\t  %d",indices_param[j]);
         	UF_UI_write_listing_window(str);
         }
         if (count_param>0) { count_param=0 ; UF_free(indices_param); }
         
         count++ ;
      }

      if (obj_count>0) { obj_count=0 ; UF_free(tags); }

      UF_UI_ONT_refresh();
      UF_UI_toggle_stoplight(0);

          break ;
          case 6 :
            UF_UI_open_listing_window();
            UF_UI_write_listing_window("\n#============================================================");
            UF_UI_write_listing_window("\n Автор:");
            UF_UI_write_listing_window("\n\t _________________________________________________________.");
            UF_UI_write_listing_window("\n#============================================================");
            UF_UI_write_listing_window("\n Выделите необходимые операции и нажмите 'Read ....s'");
            UF_UI_write_listing_window("\n");
            UF_UI_write_listing_window("\n#============================================================\n$$");
          //UF_UI_close_listing_window () ;
          break ;
          default : break ;
        }
   }

  } // end while uc1603

 //UF_DISP_refresh ();

 return (0);
}
