#include <OALib/oacontrol.h>
#include <curl/curl.h>
#include <OALib/oa_parameter.h>
#include <QDebug>
OAControl::OAControl()
{

}
//callback function to write data in memory.
int
WriteMemoryCallback (void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *) userp;

    mem->buffer = (char*)realloc (mem->buffer, mem->size + realsize + 1);
    if (mem->buffer == NULL)
    {
        /* out of memory! */
        qDebug ("not enough memory (realloc returned NULL)\n");
        return -1;
    }

    memcpy (&(mem->buffer[mem->size]), contents, realsize);
    mem->size += realsize;

    //terminated with '\0'.
    mem->buffer[mem->size] = 0;

    return realsize;
}

qint32
OAControl::postLoginInfoAndSaveCookie(QString username,QString password)
{

    qint32 ret = 0;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:";
    char postBuffer[256];

    if(username.isEmpty() || password.isEmpty())
    {
        return -1;
    }

    memset(postBuffer,0,sizeof(postBuffer));
    sprintf(postBuffer,"USERNAME=%s&PASSWORD=%s&x=22&y=33",username.toStdString().c_str(),password.toStdString().c_str());

    MemoryStruct chunk;

    chunk.buffer = (char*)malloc (1); /* will be grown as needed by the realloc above */
    chunk.size = 0; /* no data at this point */

    //do initial work.
    curl_global_init (CURL_GLOBAL_ALL);
    curl = curl_easy_init ();
    if (curl == NULL)
    {
        qDebug("curl_easy_init () failed!\n");
        return -1;
    }

    headerlist = curl_slist_append (headerlist, buf);
    if (headerlist == NULL)
    {
        qDebug("curl_slist_append() failed!\n");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, str_url_login);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

    //post previous cookie file.
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, TMP_COOKIE_FILE);

    //save new cookie file.
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, TMP_COOKIE_FILE);
    //////////////////////
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postBuffer);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,strlen(postBuffer));

    //set callback function to save data in Memory returned from server.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void* )&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    //  /**
    //   * connect timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20);
    //  /**
    //   * receive timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
    //  curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
    res = curl_easy_perform (curl);
    if (res != CURLE_OK)
    {
        qDebug ("post data failed: %s\n", curl_easy_strerror (res));
        ret = -1;
    }
    else
    {
        qDebug ("received %d bytes\n", chunk.size);
        qDebug("%s\n", chunk.buffer);
        //      for (i = 0; i < chunk.size; i++)
        //    {
        //      printf ("%02x ", (unsigned char) chunk.buffer[i]);
        //    }
        //      printf ("\n");

        /*
        * check login state.
        * if username or password is not correct,
        * if login failed,
        * the return back content will contains fixed strings.
        * so,we can just search this string in buffer,
        * if find it ,then login failed.
        * otherwise login success!
        */
        do
        {
            qDebug ("searching key words <xitongdenglu> ... ... ");
            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_xitongdenglu) != NULL)
            {
                qDebug ("fint it!\n");
                ret = 0;
            }
            else
            {
                //if not find xitongdenglu,then no need to search next key word.
                qDebug ("not find!\n");
                ret = -1;
                break;
            }

            qDebug ("searching key words <yonghuminghuomimacuowu> ... ... ");
            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_yonghuminghuomimacuowu) != NULL)
            {
                qDebug ("fint it!\n");
                ret = -1;
            }
            else
            {
                qDebug ("not find!\n");
                ret = 0;
            }
        }
        while (0);
    }
    /* always cleanup */
    curl_easy_cleanup (curl);

    /* free slist */
    curl_slist_free_all (headerlist);

    if (chunk.buffer)
    {
        free (chunk.buffer);
        chunk.buffer = NULL;
    }

    curl_global_cleanup ();
    return ret;
}
qint32
OAControl::getLoginInfoAndSaveCookie(void)
{
    int ret = 0;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:";

    MemoryStruct chunk;

    chunk.buffer = (char*)malloc (1); /* will be grown as needed by the realloc above */
    chunk.size = 0; /* no data at this point */

    //do initial work.
    curl_global_init (CURL_GLOBAL_ALL);
    curl = curl_easy_init ();
    if (curl == NULL)
    {
        qDebug("curl_easy_init () failed!\n");
        return -1;
    }
    headerlist = curl_slist_append (headerlist, buf);
    if (headerlist == NULL)
    {
        qDebug("curl_slist_append() failed!\n");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, str_url_logininfo);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    //no body data,so here set to 1L.
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

    //post previous cookie file.
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, TMP_COOKIE_FILE);

    //save new cookie file.
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, TMP_COOKIE_FILE);

    //set callback function to save data in Memory returned from server.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void* )&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    //  /**
    //   * connect timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20);
    //  /**
    //   * receive timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
    //  curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    res = curl_easy_perform (curl);
    if (res != CURLE_OK)
    {
        qDebug ("get data failed: %s\n", curl_easy_strerror (res));
        ret = -1;
    }
    else
    {

        qDebug ("received %d bytes\n", chunk.size);

        //      printf ("%s\n", chunk.buffer);
        //      for (i = 0; i < chunk.size; i++)
        //	{
        //	  printf ("%02x ", (unsigned char) chunk.buffer[i]);
        //	}
        //      printf ("\n");
        /**
          * check login information.
          * the return data will contain some fixed string,
          * for example:
          * parent.parent.location="relogin.php";
          * parent.parent.location="/general/exit.php";
          * parent.main.location="/general/person_info";
          *
          * onclick="person_info();"
          * onclick="re_login();"
          *
          * ... ...
          * if we can find these strings,then means we get login information success.
          * otherwise failed.
          */
        do
        {

            printf ("searching key word <nizhengzaishiyongdadiwenhuanchuanmenjituan> ... ... ");
            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_nizhengzaishiyongdadiwenhuanchuanmenjituan) == NULL)
            {

                //if search this failed,
                //then no need to search next key word.
                ret = -1;
                break;
            }
            else
            {

                ret = 0;
            }


            printf ("searching key word <querenyaozhuxiaoma> ... ... ");
            if (strstr ((char*)chunk.buffer,(char*)flag_gb2312_querenyaozhuxiaoma) == NULL)
            {

                //if search this failed,
                //then no need to search next key word.
                ret = -1;
                break;
            }
            else
            {
                ret = 0;
            }


            printf ("searching key word <zhuomian> ... ... ");
            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_zhuomian) == NULL)
            {
                //if search this failed,
                //then no need to search next key word.
                ret = -1;
                break;
            }
            else
            {
                ret = 0;
            }


            printf ("searching key word <jiemian> ... ... ");

            if (strstr ((char*)chunk.buffer,(char*) flag_gb2312_jiemian) == NULL)
            {
                //if search this failed,
                //then no need to search next key word.
                ret = -1;
                break;
            }
            else
            {
                ret = 0;
            }


            printf ("searching key word <tuichuxitong> ... ... ");
            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_tuichuxitong) == NULL)
            {
                //if search this failed,
                //then no need to search next key word.
                ret = -1;
                break;
            }
            else
            {
                ret = 0;
            }
        }
        while (0);
    }
    /* always cleanup */
    curl_easy_cleanup (curl);
    /* free slist */
    curl_slist_free_all (headerlist);

    if (chunk.buffer)
    {
        free (chunk.buffer);
        chunk.buffer = NULL;
    }

    curl_global_cleanup ();
    return ret;
}
qint32
OAControl::getAttendanceTableAndSaveCookie(void)
{
    int ret = 0;
    CURL *curl;
    CURLcode res;
    int i, j;
    unsigned int code_gb2312;
    unsigned int tmp1, tmp2;

    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:";

    MemoryStruct chunk;

    chunk.buffer = (char*)malloc (1); /* will be grown as needed by the realloc above */
    chunk.size = 0; /* no data at this point */

    /**
      * do initial work.
      */
    curl_global_init (CURL_GLOBAL_ALL);
    curl = curl_easy_init ();
    if (curl == NULL)
    {
        printf("curl_easy_init () failed!\n");
        return -1;
    }
    headerlist = curl_slist_append (headerlist, buf);
    if (headerlist == NULL)
    {
        printf("curl_slist_append() failed!\n");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, str_url_attendance_table);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    /**
      * GET method.
      * no body data,so here set to 1L.
      */
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    /**
      * post previous cookie file.
      */
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, TMP_COOKIE_FILE);
    /**
      * save new cookie file.
      */
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, TMP_COOKIE_FILE);

    /**
      * set callback function to save data in Memory returned from server.
      */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void* )&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    //  /**
    //   * connect timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20);
    //  /**
    //   * receive timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
    //  curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    res = curl_easy_perform (curl);
    if (res != CURLE_OK)
    {
        printf ("get data failed: %s\n", curl_easy_strerror (res));
        ret = -1;
    }
    else
    {
            printf ("received %d bytes\n", chunk.size);
        //      printf ("%s\n", chunk.buffer);
        //
        //      for (i = 0; i < chunk.size; i++)
        //	{
        //	  printf ("%02x ", (unsigned char) chunk.buffer[i]);
        //	}
        //      printf ("\n");


        //search fixed string in buffer to detect if get success!

        do
        {

            printf ("searching key words <diyicidengji> ... ... ");

            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_first_register) == NULL)
            {

                // if not search this key word,no need to search next key word.
                ret = -1;
                break;
            }
            else
            {
                ret = 0;
            }

            //diercidengji
            printf ("searching key words <diercidengji> ... ... ");
            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_second_register) == NULL)
            {

                //if not search this key word,no need to search next key word.
                ret = -1;
                break;
            }
            else
            {

                ret = 0;
            }
            //shangbandengji

            printf ("searching key words <shangbandengji> ... ...");

            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_shangbandengji) == NULL)
            {

                //if not search this key word,no need to search next key word.
                ret = -1;
                break;
            }
            else
            {
                ret = 0;
            }

            //search fixed string in buffer to detect if get success!
            //xiabandengji


            printf ("searching key words <xiabandengji> ...\t");

            if (strstr ((char*)chunk.buffer, (char*)flag_gb2312_xiabandengji) == NULL)
            {
                //if not search this key word,no need to search next key word.
                ret = -1;
                break;
            }
            else
            {
                ret = 0;
            }
        }
        while (0);
    }

    /* always cleanup */
    curl_easy_cleanup (curl);
    /* free slist */
    curl_slist_free_all (headerlist);

    if (chunk.buffer)
    {
        free (chunk.buffer);
        chunk.buffer = NULL;
    }

    curl_global_cleanup ();

    return ret;
}
qint32
OAControl::postAttenanceOnAndSaveCookie(void)
{
    CURL *curl;
     CURLcode res;
     int ret;

     struct curl_slist *headerlist = NULL;
     static const char buf[] = "Expect:";

     MemoryStruct chunk;

     chunk.buffer = (char*)malloc (1); /* will be grown as needed by the realloc above */
     chunk.size = 0; /* no data at this point */

     /**
      * do initial work.
      */
     curl_global_init (CURL_GLOBAL_ALL);
     curl = curl_easy_init ();
     if (curl == NULL)
       {
         printf ("curl_easy_init () failed!\n");
         return -1;
       }
     headerlist = curl_slist_append (headerlist, buf);
     if (headerlist == NULL)
       {
         printf("curl_slist_append() failed!\n");
         return -1;
       }

     curl_easy_setopt(curl, CURLOPT_URL, str_url_auto_on);
     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
     /**
      * post previous cookie file.
      */
     curl_easy_setopt(curl, CURLOPT_COOKIEFILE, TMP_COOKIE_FILE);
     /**
      * save new cookie file.
      */
     curl_easy_setopt(curl, CURLOPT_COOKIEJAR, TMP_COOKIE_FILE);
     /**
      * zero bytes data need to be post.
      */
     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, NULL);
     curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);

     /**
      * set callback function to save data in Memory returned from server.
      */
     curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void* )&chunk);
     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

   //  /**
   //   * connect timeout 20s.
   //   */
   //  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20);
   //  /**
   //   * receive timeout 20s.
   //   */
   //  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
   //  curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

   #ifdef SKIP_PEER_VERIFICATION
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
   #endif

   #ifdef SKIP_HOSTNAME_VERFICATION
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
   #endif
     res = curl_easy_perform (curl);
     if (res != CURLE_OK)
       {
         printf ("post data failed: %s\n", curl_easy_strerror (res));
         ret = -1;
       }
     else
       {
         printf ("received %d bytes\n", chunk.size);
         //      printf ("%s\n", chunk.buffer);
         /**
          * search fixed string in buffer to detect if get success!
          * yikaoqin
          */
   //      printf ("searching key words <yikaoqin> ...\t");
   //      if (strstr (chunk.buffer, flag_gb2312_yikaoqin) == NULL)
   //	{
   //	  printf ("not find!\n");
   //	  ret = -1;
   //	}
   //      else
   //	{
   //	  printf ("find it!\n");
   //	  ret = 0;
   //	}
         ret = 0;
       }

     /* always cleanup */
     curl_easy_cleanup (curl);

     /* free slist */
     curl_slist_free_all (headerlist);

     if (chunk.buffer)
       {
         free (chunk.buffer);
         chunk.buffer = NULL;
       }

     curl_global_cleanup ();

     return ret;
}
qint32
OAControl::postAttendanceOffAndSaveCookie(void)
{
    CURL *curl;
      CURLcode res;
      struct curl_slist *headerlist = NULL;
      static const char buf[] = "Expect:";
      int ret = 0;
      MemoryStruct chunk;

      chunk.buffer =(char*) malloc (1); /* will be grown as needed by the realloc above */
      chunk.size = 0; /* no data at this point */

      /**
       * do initial work.
       */
      curl_global_init (CURL_GLOBAL_ALL);
      curl = curl_easy_init ();
      if (curl == NULL)
        {
          printf ("curl_easy_init () failed!\n");
          return -1;
        }
      headerlist = curl_slist_append (headerlist, buf);
      if (headerlist == NULL)
        {
          printf("curl_slist_append() failed!\n");
          return -1;
        }

      curl_easy_setopt(curl, CURLOPT_URL, str_url_auto_off);
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

      /**
       * post previous cookie file.
       */
      curl_easy_setopt(curl, CURLOPT_COOKIEFILE, TMP_COOKIE_FILE);
      /**
       * save new cookie file.
       */
      curl_easy_setopt(curl, CURLOPT_COOKIEJAR, TMP_COOKIE_FILE);
      /**
       * zero bytes data need to be post.
       */
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, NULL);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);

      /**
       * set callback function to save data in Memory returned from server.
       */
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void* )&chunk);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    //  /**
    //   * connect timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20);
    //  /**
    //   * receive timeout 20s.
    //   */
    //  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
    //  curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

    #ifdef SKIP_PEER_VERIFICATION
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    #endif

    #ifdef SKIP_HOSTNAME_VERFICATION
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    #endif
      res = curl_easy_perform (curl);

      if (res != CURLE_OK)
        {
          printf ("post data failed: %s\n", curl_easy_strerror (res));
          ret = -1;
        }
      else
        {
          printf ("received %d bytes\n", chunk.size);
          // printf ("%s\n", chunk.buffer);
          ret = 0;
        }

      /* always cleanup */
      curl_easy_cleanup (curl);

      /* free slist */
      curl_slist_free_all (headerlist);

      if (chunk.buffer)
        {
          free (chunk.buffer);
          chunk.buffer = NULL;
        }

      curl_global_cleanup ();
      return ret;
}

