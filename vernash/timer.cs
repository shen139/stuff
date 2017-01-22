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

namespace Vernash
{
    public class timer
    {
        DateTime startTime;

        public timer()
        {
            restart();
        }

        public void restart()
        {
            startTime = DateTime.Now;
        }

        public decimal getTimeMS()
        {
            TimeSpan duration = DateTime.Now - startTime;

            return (decimal)duration.TotalMilliseconds / 1024;
        }
    }
}
