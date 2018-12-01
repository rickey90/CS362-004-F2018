import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {

   private boolean printIndex = false; //Parameters are scheme, host, port, path, & query test
   private boolean printStatus = false;

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   static public void checkTrue(String url, boolean check)
   {
      if(check != true)
      {
         System.out.println("Url: " + url + " is invalid.\t\tExpected: valid -- FAIL");
      }
      else
      {
         System.out.println("Url: " + url + " is valid.\t\tExpected: valid -- PASS");
      }
   }

   static public void checkFalse(String url, boolean check)
   {
      if(check != false)
      {
         System.out.println("Url: " + url + " is valid.\t\tExpected: invalid -- FAIL");
      }
      else
      {
         System.out.println("Url: " + url + " is invalid.\t\tExpected: invalid -- PASS");
      }
   }
   
   public void testManualTest()
   {
      //You can use this function to implement your manual testing   
    //Without Fragments

       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
       System.out.println("\nUrlValidator.NO_FRAGMENTS: \n");

           // Valid Scheme
           System.out.println("\nTesting scheme: Should return True: ");
           System.out.println("http://www.amazon.com");
           System.out.println(urlVal.isValid("http://www.amazon.com"));
           System.out.println("www.amazon.com");
           System.out.println(urlVal.isValid("www.amazon.com"));

           // Invalid Scheme
           System.out.println("\nTesting scheme: Should return False: ");
           System.out.println("httpss://www.amazon.com");
           System.out.println(urlVal.isValid("://www.amazon.com"));
           System.out.println("://www.amazon.com");
           System.out.println(urlVal.isValid("://www.amazon.com"));
           System.out.println("http://w.amazon.com");
           System.out.println(urlVal.isValid("http://w.amazon.com"));


           // Valid Authority
           System.out.println("\nTesting Authority: Should return True: ");
           System.out.println("http://www.amazon.com");
           System.out.println(urlVal.isValid("http://www.amazon.com"));
           System.out.println("http://www.oregonstate.edu");
           System.out.println(urlVal.isValid("http://www.oregonstate.edu"));

           // Invalid Authority
           System.out.println("\nTesting Authority: Should return False: ");
           System.out.println("http://www.amazon~.com");
           System.out.println(urlVal.isValid("http://www.amazon~.com"));
           System.out.println("http://www.amazon");
           System.out.println(urlVal.isValid("http://www.amazon"));
           System.out.println("http://"); //blank
           System.out.println(urlVal.isValid("http:// "));

           // Valid Port
           System.out.println("\nTesting Port: Should return True: ");
           System.out.println("http://www.amazon.com:80");
           System.out.println(urlVal.isValid("http://www.amazon.com:80"));
           System.out.println("http://www.amazon.com:0");
           System.out.println(urlVal.isValid("http://www.amazon.com:0"));

           //Invalid Port
           System.out.println("\nTesting Port: Should return False: ");
           System.out.println("http://www.amazon.com:"); //Blank port
           System.out.println(urlVal.isValid("http://www.amazon.com:"));
           System.out.println("http://www.amazon.com:abc");
           System.out.println(urlVal.isValid("http://www.amazon.com:abc"));
          

           // Valid Path
           System.out.println("\nTesting Path: Should return True: ");
           System.out.println("http://www.amazon.com/abc");
           System.out.println(urlVal.isValid("http://www.amazon.com/abc"));
           System.out.println("http://www.amazon.com/");
           System.out.println(urlVal.isValid("http://www.amazon.com/"));

           // Invalid Path
           System.out.println("\nTesting Path: Should return False: ");
           System.out.println("http://www.amazon.com//test1");
           System.out.println(urlVal.isValid("http://www.gamazon.com//test1"));
           System.out.println("http://www.amazon.com/../");
           System.out.println(urlVal.isValid("http://www.amazon.com/../"));

           // Valid Queries
           System.out.println("\nTesting Queries: Should return True:");
           System.out.println("http://www.amazon.com?action=view");
           System.out.println(urlVal.isValid("http://www.amazon.com?action=view"));
           System.out.println("http://www.google.com?first=this+is+a+field");
           System.out.println(urlVal.isValid("http://www.google.com?first=this+is+a+field"));
           
           // InValid Queries
           System.out.println("\nTesting Queries: Should return False: ");
           System.out.println("http://www.amazon.com?action=");
           System.out.println(urlVal.isValid("http://www.amazon.com?action="));
           System.out.println("http://www.google.com??action=view");
           System.out.println(urlVal.isValid("http://www.google.com??action=view"));

       // End without fragments
       System.out.println("\nEnd UrlValidator.NO_FRAGMENTS: \n");

       //ALLOW LOCAL URLS

       UrlValidator urlValLocalUrl = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
       System.out.println("\nUrlValidator.ALLOW_LOCAL_URLS: \n");

           // Valid Scheme
           System.out.println("\nTesting scheme: Should return True: ");
           System.out.println("http://www.amazon.com");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com"));
           System.out.println("www.amazon.com");
           System.out.println(urlValLocalUrl.isValid("www.amazon.com"));

           // Invalid Scheme
           System.out.println("\nTesting scheme: Should return False: ");
           System.out.println("httpss://www.amazon.com");
           System.out.println(urlValLocalUrl.isValid("://www.amazon.com"));
           System.out.println("://www.amazon.com");
           System.out.println(urlValLocalUrl.isValid("://www.amazon.com"));

           // Valid Authority
           System.out.println("\nTesting Authority: Should return True: ");
           System.out.println("http://www.amazon.com");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com"));
           System.out.println("http://www.oregonstate.edu");
           System.out.println(urlValLocalUrl.isValid("http://www.oregonstate.edu"));

           // Invalid Authority
           System.out.println("\nTesting Authority: Should return False: ");
           System.out.println("http://www.amazon~.com");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon~.com"));
           System.out.println("http://www.amazon");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon"));
           System.out.println("http://"); //blank
           System.out.println(urlValLocalUrl.isValid("http:// "));

           // Valid Port
           System.out.println("\nTesting Port: Should return True: ");
           System.out.println("http://www.amazon.com:80");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com:80"));
           System.out.println("http://www.amazon.com:0");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com:0"));

           //Invalid Port
           System.out.println("\nTesting Port: Should return False: ");
           System.out.println("http://www.amazon.com:"); //Blank port
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com:"));
           System.out.println("http://www.amazon.com:abc");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com:abc"));
          

           // Valid Path
           System.out.println("\nTesting Path: Should return True: ");
           System.out.println("http://www.amazon.com/abc");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com/abc"));
           System.out.println("http://www.amazon.com/");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com/"));

           // Invalid Path
           System.out.println("\nTesting Path: Should return False: ");
           System.out.println("http://www.amazon.com//test1");
           System.out.println(urlValLocalUrl.isValid("http://www.gamazon.com//test1"));
           System.out.println("http://www.amazon.com/../");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com/../"));

           // Valid Queries
           System.out.println("\nTesting Queries: Should return True:");
           System.out.println("http://www.amazon.com?action=view");
           System.out.println(urlValLocalUrl.isValid("http://www.amazon.com?action=view"));
           System.out.println("http://www.google.com?first=this+is+a+field");
           System.out.println(urlValLocalUrl.isValid("http://www.google.com?first=this+is+a+field"));
           
            // InValid Queries
           System.out.println("\nTesting Queries: Should return False: ");
           System.out.println("http://www.amazon.com?action=");
           System.out.println(urlVal.isValid("http://www.amazon.com?action="));
           System.out.println("http://www.google.com??action=view");
           System.out.println(urlVal.isValid("http://www.google.com??action=view"));
   ;

       // End local URL
       System.out.println("\nEnd UrlValidator.ALLOW_LOCAL_URLS: \n");


       // All Schemes

       UrlValidator urlValAllScheme = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println("\nUrlValidator.ALLOW_ALL_SCHEMES: \n");

           // Valid Scheme
           System.out.println("\nTesting scheme: Should return True: ");
           System.out.println("http://www.amazon.com");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com"));
           System.out.println("www.amazon.com");
           System.out.println(urlValAllScheme.isValid("www.amazon.com"));

           // Invalid Scheme
           System.out.println("\nTesting scheme: Should return False: ");
           System.out.println("httpss://www.amazon.com");
           System.out.println(urlValAllScheme.isValid("://www.amazon.com"));
           System.out.println("://www.amazon.com");
           System.out.println(urlValAllScheme.isValid("://www.amazon.com"));

           // Valid Authority
           System.out.println("\nTesting Authority: Should return True: ");
           System.out.println("http://www.amazon.com");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com"));
           System.out.println("http://www.oregonstate.edu");
           System.out.println(urlValAllScheme.isValid("http://www.oregonstate.edu"));

           // Invalid Authority
           System.out.println("\nTesting Authority: Should return False: ");
           System.out.println("http://www.amazon~.com");
           System.out.println(urlValAllScheme.isValid("http://www.amazon~.com"));
           System.out.println("http://www.amazon");
           System.out.println(urlValAllScheme.isValid("http://www.amazon"));
           System.out.println("http://"); //blank
           System.out.println(urlValAllScheme.isValid("http:// "));

           // Valid Port
           System.out.println("\nTesting Port: Should return True: ");
           System.out.println("http://www.amazon.com:80");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com:80"));
           System.out.println("http://www.amazon.com:0");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com:0"));

           //Invalid Port
           System.out.println("\nTesting Port: Should return False: ");
           System.out.println("http://www.amazon.com:"); //Blank port
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com:"));
           System.out.println("http://www.amazon.com:abc");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com:abc"));
          

           // Valid Path
           System.out.println("\nTesting Path: Should return True: ");
           System.out.println("http://www.amazon.com/abc");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com/abc"));
           System.out.println("http://www.amazon.com/");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com/"));

           // Invalid Path
           System.out.println("\nTesting Path: Should return False: ");
           System.out.println("http://www.amazon.com//test1");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com//test1"));
           System.out.println("http://www.amazon.com/../");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com/../"));

           // Valid Queries
           System.out.println("\nTesting Queries: Should return True:");
           System.out.println("http://www.amazon.com?action=view");
           System.out.println(urlValAllScheme.isValid("http://www.amazon.com?action=view"));
           System.out.println("http://www.google.com?first=this+is+a+field");
           System.out.println(urlValAllScheme.isValid("http://www.google.com?first=this+is+a+field"));
           
            // InValid Queries
           System.out.println("\nTesting Queries: Should return False: ");
           System.out.println("http://www.amazon.com?action=");
           System.out.println(urlVal.isValid("http://www.amazon.com?action="));
           System.out.println("http://www.google.com??action=view");
           System.out.println(urlVal.isValid("http://www.google.com??action=view"));


       // End ALLOW_ALL_SCHEMES
       System.out.println("\nEnd UrlValidator.ALLOW_ALL_SCHEMES: \n");

      
   }
   
   
   public void testYourFirstPartition() //first partition will be the url scheme
   {
      //You can use this function to implement your First Partition testing      
      System.out.println("\nPartition 1: Testing Scheme");
      System.out.println("------------------------------------------------------------------");
      UrlValidator urlVal = new UrlValidator();
      //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      
      //test known valid url schemes
      checkTrue("http://www.google.com", urlVal.isValid("http://www.google.com"));
      checkTrue("https://www.google.com", urlVal.isValid("https://www.google.com"));
      checkTrue("ftp://www.google.com", urlVal.isValid("ftp://www.goolge.com"));
      checkTrue("h3t://www.google.com", urlVal.isValid("h3t://www.google.com"));

      //test known invalid url schemes
      checkFalse("h$$p://www.google.com", urlVal.isValid("h$$p://www.google.com"));
      checkFalse("ftads://www.google.com", urlVal.isValid("ftads://www.google.com"));
      checkFalse("@@://www.google.com", urlVal.isValid("@@://www.google.com"));
      
   }
   
   public void testYourSecondPartition(){
      //You can use this function to implement your Second Partition testing  
      System.out.println("\nPartition 2: Testing Authority");
      System.out.println("------------------------------------------------------------------");
      UrlValidator urlVal = new UrlValidator();
      //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      
      //test known valid url authority
      checkTrue("http://go.com", urlVal.isValid("http://go.com"));
      checkTrue("http://www.google.com", urlVal.isValid("http://www.google.com"));
      checkTrue("http://255.255.255.255", urlVal.isValid("http://255.255.255.255"));
      checkTrue("http://www.oregonstate.edu", urlVal.isValid("http://www.oregonstate.edu"));
      
      //test known invalid authority
      checkFalse("http://www-google.com", urlVal.isValid("http://www-google.com"));
      checkFalse("http://www/google/com", urlVal.isValid("http://www/google/com"));
      checkFalse("http://0.0.0", urlVal.isValid("http://0.0.0"));
      checkFalse("http://256.256.256.256", urlVal.isValid("http://256.256.256.256"));

   }
   
   public void testYourThirdPartition() {
      System.out.println("\nPartition 3: Testing Port");
      System.out.println("------------------------------------------------------------------");
      UrlValidator urlVal = new UrlValidator();
      //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      
      //test known valid url port
      checkTrue("http://www.google.com:80", urlVal.isValid("http://www.google.com:80"));
      checkTrue("http://www.google.com:0", urlVal.isValid("http://www.google.com:0"));
      checkTrue("http://www.google.com:65535", urlVal.isValid("http://www.google.com:65535"));
      
      //test known invalid url port
      checkFalse("http://www.google.com:-10", urlVal.isValid("http://www.google.com:-10"));
      checkFalse("http://www.google.com:abc", urlVal.isValid("http://www.google.com:abc"));
      checkFalse("http://www.google.com:65636", urlVal.isValid("http://www.google.com:65636"));
      
   }
   
   public void testYourFourthPartition() {
      System.out.println("\nPartition 4: Testing Path");
      System.out.println("------------------------------------------------------------------");
      UrlValidator urlVal = new UrlValidator();
      //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      
      //test known valid url path
      checkTrue("http://www.google.com/abc", urlVal.isValid("http://www.google.com/abc"));
      checkTrue("http://www.google.com/is/good", urlVal.isValid("http://www.google.com/is/good"));
      checkTrue("http://www.google.com/still/g@@d/", urlVal.isValid("http://www.google.com/still/g@@d/"));
      
      //test known invalid url path
      checkFalse("http://www.google.com//abc", urlVal.isValid("http://www.google.com//abc"));
      checkFalse("http://www.google.com/not//good", urlVal.isValid("http://www.google.com/not//good"));
      checkFalse("http://www.google.com/../", urlVal.isValid("http://www.google.com/../"));
   }
   
   public void testYourFifthPartition() {
      System.out.println("\nPartition 5: Testing Query");
      System.out.println("------------------------------------------------------------------");
      UrlValidator urlVal = new UrlValidator();
      //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      
      //test known valid url query
      checkTrue("http://www.google.com?action=view", urlVal.isValid("http://www.google.com?action=view"));
      checkTrue("http://www.google.com?q=asdfsafa", urlVal.isValid("http://www.google.com?q=asdfsafa"));
      checkTrue("http://www.google.com?first=this+is+a+field", urlVal.isValid("http://www.google.com?first=this+is+a+field"));
      
      //test known invalid url query
      checkFalse("http://www.google.com!action=view", urlVal.isValid("http://www.google.com!action=view"));
      checkFalse("http://www.google.com:q=asdfsafa", urlVal.isValid("http://www.google.com:q=asdfsafa"));
   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
      //You can use this function for programming based testing
      Random rand = new Random();//make a random object
      int n = -1; 
      int o = -1;
      int p = -1;
      int q = -1;
      int r = -1;
      //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
      //UrlValidator urlVal = new UrlValidator();
      
      //get random # within the range of the sub array
      boolean preValid = true;//to compare the .valid of each string appended. Change to false if .valid is false.
      for (int i = 0; i < 10; ++i) {
        //System.out.printf("\tSTARTING LOOP\n");
        
        StringBuilder testBuffer = new StringBuilder();//this must be from the "junit" import on line 18. builds the string?
        
        /** testing that a known ‘ftp’ url breaks.
        if (urlVal.isValid("ftp://foo.bar.com/")) {
              System.out.println("url is valid");
        } 
        else {
              System.out.println("url is invalid");
        }**/
          n = rand.nextInt(8);//8 is the maximum and the 1 is the minimum.
          testBuffer.append(testUrlScheme[n].item);
          if(!testUrlScheme[n].valid)        {preValid = false;}  
          //System.out.printf("\tScheme PASSED");

          o = rand.nextInt(17);//17 is the maximum and the 0 is the minimum.
          testBuffer.append(testUrlAuthority[o].item);
          if(!testUrlAuthority[o].valid)  {preValid = false;}  
          //System.out.printf("\tAuthority PASSED");
          
          p = rand.nextInt(6);//6 is the maximum and the 0 is the minimum.
          testBuffer.append(testUrlPort[p].item);
          if(!testUrlPort[p].valid)       {preValid = false;}  
          //System.out.printf("\tPort PASSED");

          q = rand.nextInt(9);//9 is the maximum and the 0 is the minimum.
          testBuffer.append(testPath[q].item);
          if(!testPath[q].valid)          {preValid = false;}   
          //System.out.printf("\tPath PASSED");

          r = rand.nextInt(2);//2 is the maximum and the 0 is the minimum.
          testBuffer.append(testUrlQuery[r].item);
          if(!testUrlQuery[r].valid)      {preValid = false;}  
          //System.out.printf("\tQuery PASSED\n");
         
          //System.out.printf("Hello, World \n\t%s\n", testBuffer); 
          String url = testBuffer.toString();//convert the "testbuffer" to a string called "url"
          System.out.printf("\tSENDING " + url +" TO ISVALID()\n");
          boolean postVal = urlVal.isValid(url);
          System.out.printf("\tISVALID() RETURNED " + postVal + " = postVal\n");
          
          System.out.printf(preValid + "\treturned  " + postVal + "\turl=\t" + testBuffer + "\n"); 
         }//end of URL building 4-loop
      
         //boolean trueURL = urlVal.isValid("http://www.google.com");
         //System.out.printf(trueURL + "   http://www.google.com...this should be true...\n");
         //trueURL = urlVal.isValid("http://www.amazon.com");
         //System.out.printf(trueURL + "   http://www.amazon.com...this should be true...\n");     
   }//end of testIsValid

}
