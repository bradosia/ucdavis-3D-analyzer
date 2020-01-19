/*
 * Name        : PI WEB API for UC Davis
 * Author      : Brad Lee
 * Version     : 1.00
 * License     : GNU LGPL v3
 *
 */

/*
 * piwebapi-ucdavis 1.0
 */
#include "UCDavis3DAnalyzer/osisoft_pi_api.h"

/*
 * UCD3DA = UC Davis 3D Analyzer
 */
namespace UCD3DA {

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
  s->append((char *)ptr, size * nmemb);
  return size * nmemb;
}

rapidjson::Document HTTPS_GET_JSON(std::string URI) {
  CURL *curl;
  CURLcode res;
  std::string bufferString;
  rapidjson::Document resJSON_Doc;

  printf("HTTPS_GET_JSON called on: %s\n",URI.c_str());

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

  if (curl) {

    curl_easy_setopt(curl, CURLOPT_URL, URI.c_str());
    // curl_easy_setopt(curl, CURLOPT_CAINFO,
    // "/etc/ssl/certs/ca-certificates.crt");

    /* Disable SSL/TLS verification
     * TODO: Write the SSL Certificate Manager
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    /*
     * TODO: Write the SSL Certificate Manager
     */
    // getCertificates(global);
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* setup callbacks */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bufferString);
    /* Perform the request, res will get the return code */

    res = curl_easy_perform(curl);
    resJSON_Doc.Parse(bufferString.c_str());

    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
#ifdef DEBUG_JSON
    std::cout << bufferString << std::endl;
#endif

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return resJSON_Doc;
}

void printJSON_value(const rapidjson::Value &a, unsigned int depth) {
  if (a.IsArray()) {
    rapidjson::SizeType n =
        a.Size(); // rapidjson uses SizeType instead of size_t.
    for (rapidjson::SizeType i = 0; i < n; i++) {
      if (a[i].IsObject()) {
        rapidjson::Value::ConstMemberIterator itr = a[i].MemberBegin();
        printJSON_iterator(itr, ++depth);
      } else if (a[i].IsArray()) {
        const rapidjson::Value &aa = a[i];
        printJSON_value(aa, ++depth);
      }
    }
  }
}

void printJSON_iterator(rapidjson::Value::ConstMemberIterator &itr,
                        unsigned int depth) {
  static const char *kTypeNames[] = {"Null",  "False",  "True",  "Object",
                                     "Array", "String", "Number"};
  printf("Type of member %s is %s\n", itr->name.GetString(),
         kTypeNames[itr->value.GetType()]);
  if (itr->value.GetType() == 3) {
    const rapidjson::Value &a = itr->value;
    for (rapidjson::Value::ConstMemberIterator itr2 = a.MemberBegin();
         itr2 != a.MemberEnd(); ++itr2) {
      printJSON_iterator(itr2, ++depth);
    }
  } else if (itr->value.GetType() == 4) {
    const rapidjson::Value &a = itr->value;
    printJSON_value(a, ++depth);
  }
}

void getSettingsFile(std::string settingsFileString, std::string &inputURIString, std::string &outputFileString){
    // Check if inputFile exists
    {
      std::fstream inputFile;
      inputFile.open(settingsFileString, std::fstream::in);
      if (!inputFile) {
        printf("FATAL ERROR: Could not open input file: %s\n",
               settingsFileString.c_str());
        return;
      }
    }
    std::fstream settingsFile;
    printf("Opening settings file: %s\n", settingsFileString.c_str());
    settingsFile.open(settingsFileString, std::fstream::in);
    if (settingsFile) {
      char *settingsFileChar;
      unsigned int fileSize;
      rapidjson::Document d;

      settingsFile.seekg(0, std::ios::end); // set the pointer to the end
      fileSize = settingsFile.tellg();      // get the length of the file
      settingsFile.seekg(0, std::ios::beg);
      settingsFileChar = new char[fileSize + 1];
      memset(settingsFileChar, 0, sizeof(settingsFileChar[0]) * fileSize + 1);
      settingsFile.read(settingsFileChar, fileSize);

      d.Parse(settingsFileChar);
      if (d.IsObject()) {
        if (d.HasMember("URI") && d["URI"].IsString()) {
          inputURIString = d["URI"].GetString();
          printf("Input URI Set: %s\n", inputURIString.c_str());
        }
        if (d.HasMember("output") && d["output"].IsString()) {
          outputFileString = d["output"].GetString();
          printf("Output file Set: %s\n", outputFileString.c_str());
        }
      }
      delete settingsFileChar;
    } else {
      printf("No settings file used. Check settings file: %s\n", settingsFileString.c_str());
    }
}

} // namespace PWA_UCD
