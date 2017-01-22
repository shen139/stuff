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
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}