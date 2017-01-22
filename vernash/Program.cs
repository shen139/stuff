/* Vernash
 *   Stream cipher based on the Vernam cipher and Variable-Length Hashes
 *   
 * Author:  
 *   Stefano 'Shen139' Alimonti
 * 
 * Website:
 *   http://lab.openwebspider.org/vernash/
 *
 */

using System;
using System.Windows.Forms;


using System.Text;

namespace Vernash
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {

            /* Performance tests
             */
            /*
            vernash v = new vernash();

            StringBuilder longText = new StringBuilder("ABCDEFGHILMNOPQRSTUVZ0123456789");
            
            for (uint i = 0; i < 17; i++)
            {
                longText.Append(longText);
            }

            timer t = new timer();
            string enc = v.vernashCrypt(ASCIIEncoding.Default.GetBytes(longText.ToString()),"test1234567890",true, "test.vsh");
            string ms = t.getTimeMS().ToString("#0.00");

            return;
            */

            /* *********************************************************************** */
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}