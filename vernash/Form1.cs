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
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;

namespace Vernash
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public void openDialogSetDefaults()
        {
            openFileDialog.FileName = "";
            openFileDialog.Filter = "All Files|*.*";
        }

        public void saveDialogSetDefaults()
        {
            saveFileDialog.FileName = "";
            saveFileDialog.Filter = "Vernash File|*.vsh|All Files|*.*";

        }

        private byte[] openFile()
        {
            byte[] buffer = null;
            try
            {
                if (openFileDialog.ShowDialog() == DialogResult.Cancel)
                    return null;

                FileStream fileStream = new FileStream(openFileDialog.FileName, FileMode.Open);

                try
                {
                    BinaryReader br = new BinaryReader(fileStream);
                    long len = fileStream.Seek(0, SeekOrigin.End);
                    fileStream.Seek(0, SeekOrigin.Begin);

                    buffer = new byte[len];
                    br.Read(buffer, 0, (int)len);
                }
                finally
                {
                    fileStream.Close();
                }
            }
            catch (Exception exc)
            {
                buffer = null;
                MessageBox.Show("Error: " + exc.Message);
            }
            return buffer;
        }

        private bool saveFile(byte[] text)
        {
            if (text.Length == 0)
            {
                MessageBox.Show("Nothing to save!");
                return false;
            }

            if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
                return false;
            try
            {
                FileStream fileStream = new FileStream(saveFileDialog.FileName, FileMode.Create);
                BinaryWriter bw = new BinaryWriter(fileStream);

                try
                {
                    bw.Write(text);
                }
                catch (Exception exc)
                {
                    MessageBox.Show("Error: " + exc.Message);
                }
                finally
                {
                    // close the stream
                    bw.Close();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error: " + exc.Message);
                return false;
            }
            return true;

        }

        // encode password to md5 hash
        private string EncodePassword(string originalPassword)
        {
            // Instantiate MD5CryptoServiceProvider, get bytes for original password and compute hash (encoded password)
            Byte[] originalBytes = ASCIIEncoding.Default.GetBytes(originalPassword);
            Byte[] encodedBytes = new MD5CryptoServiceProvider().ComputeHash(originalBytes);

            StringBuilder result = new StringBuilder();
            for (int i = 0; i < encodedBytes.Length; i++)
            {
                result.Append(encodedBytes[i].ToString("x2"));
            }

            // Convert encoded bytes back to a 'readable' string
            return result.ToString();
        }

        private string bytesToString(byte[] b)
        {
            StringBuilder res = new StringBuilder();
            for (int i = 0; i < b.Length; i++)
            {
                res.Append(b[i].ToString("x2"));
            }

            return res.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            txtOutput.Text = string.Empty;

            if (txtTextHash.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Text");
                txtTextHash.Focus();
                return;
            }
            if ((int)numHashLength.Value == 0)
            {
                MessageBox.Show("Please Enter a Valid Number");
                numHashLength.Focus();
                return;
            }

            if (radioButton1.Checked)
            {
                // use Vernash
                vernash v = new vernash();
                txtOutput.Text = v.hashum(txtTextHash.Text, (int)numHashLength.Value);
            }
            else
            {
                byte[] hashBytes = new byte[1];
                // use System.Security.Cryptography for MD5, SHA-1, SHA-256, SHA-512
                if (radioButton2.Checked)
                {
                    // MD5
                    MD5 md5 = new MD5CryptoServiceProvider();
                    hashBytes = md5.ComputeHash(ASCIIEncoding.Default.GetBytes(txtTextHash.Text));
                }
                else if (radioButton3.Checked)
                {
                    // SHA-1
                    SHA1 sha1 = new SHA1CryptoServiceProvider();
                    hashBytes = sha1.ComputeHash(ASCIIEncoding.Default.GetBytes(txtTextHash.Text));
                }

                txtOutput.Text = bytesToString(hashBytes);
            }
        }

        // crypt a text
        private void button2_Click(object sender, EventArgs e)
        {
            txtOutput.Text = string.Empty;

            if (txtPassword.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txtPassword.Focus();
                return;
            }

            if (txtText.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Text");
                txtText.Focus();
                return;
            }

            this.Cursor = Cursors.WaitCursor;
            toolStripStatusLabel1.Text = "EnCrypting...";
            Application.DoEvents();

            timer execTime = new timer();

            vernash v = new vernash();
            string x = v.vernashCrypt(System.Text.Encoding.UTF8.GetBytes(txtText.Text.ToCharArray()), txtPassword.Text, false, string.Empty);

            this.Cursor = Cursors.Default;

            toolStripStatusLabel1.Text = "Text EnCrypted in " + execTime.getTimeMS().ToString("#0.00") + " seconds";

            txtOutput.Text = x;
        }

        // decrypt a text
        private void button3_Click(object sender, EventArgs e)
        {
            txtOutput.Text = string.Empty;

            if (txtPassword.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txtPassword.Focus();
                return;
            }

            if (txtText.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Text");
                txtText.Focus();
                return;
            }

            this.Cursor = Cursors.WaitCursor;
            toolStripStatusLabel1.Text = "DeCrypting...";
            Application.DoEvents();

            timer execTime = new timer();

            vernash v = new vernash();
            byte[] x = v.vernashDeCrypt(txtText.Text, txtPassword.Text, false, string.Empty);

            this.Cursor = Cursors.Default;

            if (x == null)
            {
                txtOutput.Text = "ERROR: Unable to DeCrypt Text!";
                toolStripStatusLabel1.Text = "Ready";
                return;
            }

            toolStripStatusLabel1.Text = "Text DeCrypted in " + execTime.getTimeMS().ToString("#0.00") + " seconds";

            txtOutput.Text = System.Text.Encoding.UTF8.GetString(x);

        }

        // copy output to text
        private void button4_Click(object sender, EventArgs e)
        {
            if (tabControl1.SelectedIndex == 0)
                txtText.Text = txtOutput.Text;       // Vernash Tab
            else if (tabControl1.SelectedIndex == 1)
                txtTextHash.Text = txtOutput.Text;   // Hash Tab
            else
                txt3DEStext.Text = txtOutput.Text;   // TripleDES

        }

        // save output to file
        private void button6_Click(object sender, EventArgs e)
        {
            saveDialogSetDefaults();
            saveFile(System.Text.Encoding.UTF8.GetBytes(txtOutput.Text));
        }

        // clear output
        private void button7_Click(object sender, EventArgs e)
        {
            txtOutput.Text = string.Empty;
        }


        // clear text
        private void button10_Click(object sender, EventArgs e)
        {
            if (tabControl1.SelectedIndex == 0)
                txtText.Text = string.Empty;        // Clean Vernash Tab's Text
            else if (tabControl1.SelectedIndex == 1)
                txtTextHash.Text = string.Empty;    // Clean Hash Tab's Text
            else
                txt3DEStext.Text = string.Empty;    // TripleDES Tab
        }


        private void Form1_Shown(object sender, EventArgs e)
        {
            txtPassword.Focus();
        }

        private void button11_Click(object sender, EventArgs e)
        {
            txtOutput.Text = string.Empty;

            if (txtPassword.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txtPassword.Focus();
                return;
            }

            if (txtText.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Text");
                txtText.Focus();
                return;
            }

            this.Cursor = Cursors.WaitCursor;
            toolStripStatusLabel1.Text = "Shuffling text...";
            Application.DoEvents();

            timer execTime = new timer();

            vernash v = new vernash();
            string x = v.scrambleText(txtText.Text, txtPassword.Text, v.genKeyPos(txtText.Text.Length,txtPassword.Text));

            this.Cursor = Cursors.Default;

            toolStripStatusLabel1.Text = "Text Shuffled in " + execTime.getTimeMS().ToString("#0.00") + " seconds";

            txtOutput.Text = x;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            txtOutput.Text = string.Empty;

            if (txtPassword.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txtPassword.Focus();
                return;
            }

            if (txtText.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Text");
                txtText.Focus();
                return;
            }

            this.Cursor = Cursors.WaitCursor;
            toolStripStatusLabel1.Text = "UnShuffling text...";
            Application.DoEvents();

            timer execTime = new timer();

            vernash v = new vernash();
            string x = v.unScrambleText(txtText.Text, txtPassword.Text, v.genKeyPos(txtText.Text.Length, txtPassword.Text));

            this.Cursor = Cursors.Default;

            toolStripStatusLabel1.Text = "Text UnShuffled in " + execTime.getTimeMS().ToString("#0.00") + " seconds";

            txtOutput.Text = x;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
                txtPassword.PasswordChar = '*';
            else
                txtPassword.PasswordChar = (char)0;

        }

        private void encryptAFileToAnotherFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // crypt a file to file
            if (txtPassword.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txtPassword.Focus();
                return;
            }

            openDialogSetDefaults();
            saveDialogSetDefaults();

            toolStripStatusLabel1.Text = "Please select a file to EnCrypt!";
            Application.DoEvents();

            byte[] buf;
            buf = openFile();
            if (buf == null)
                return;

            string text = System.Text.Encoding.UTF8.GetString(buf);
            if (text.Length == 0)
                return;

            toolStripStatusLabel1.Text = "Please select a file to save EnCrypted text!";

            if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
                return;

            toolStripStatusLabel1.Text = "EnCrypting file...";
            this.Cursor = Cursors.WaitCursor;
            Application.DoEvents();

            timer execTime = new timer();

            vernash v = new vernash();
            string x = v.vernashCrypt(buf, txtPassword.Text, true, saveFileDialog.FileName);

            this.Cursor = Cursors.Default;

            string txtStrip = "Text EnCrypted in " + execTime.getTimeMS().ToString("#0.00") + " seconds";

            toolStripStatusLabel1.Text = txtStrip;
        }

        private void openFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // open a file to text
            openDialogSetDefaults();

            byte[] buf;
            buf = openFile();
            if (buf == null)
                return;

            if (buf.Length > 100000)
                MessageBox.Show("Text too long.");
            else
                txtText.Text = System.Text.Encoding.UTF8.GetString(buf);
        }

        private void decryptAFileToAnotherFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // decrypt a file to file
            if (txtPassword.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txtPassword.Focus();
                return;
            }

            openFileDialog.FileName = "";
            openFileDialog.Filter = "Vernash File|*.vsh|All Files|*.*";

            saveFileDialog.FileName = "";
            saveFileDialog.Filter = "All Files|*.*";

            toolStripStatusLabel1.Text = "Please select a file to DeCrypt!";
            Application.DoEvents();

            byte[] buf;
            buf = openFile();
            if (buf == null)
                return;

            string text = System.Text.Encoding.UTF8.GetString(buf);
            if (text.Length == 0)
                return;
            bool vaildVernashFile = false;

            // check validity (v0.3+)
            if (text.Length > vernash.vernashFileHeader.Length)
            {
                if (text.Substring(0, 7) == vernash.vernashFileHeader)
                {
                    vaildVernashFile = true;
                }
            }

            if (vaildVernashFile == false)
            {
                txtOutput.Text = "ERROR: Invalid File (not encrypted with Vernash)!";
                toolStripStatusLabel1.Text = "Ready";
                return;
            }

            toolStripStatusLabel1.Text = "Please select a file to save DeCrypted text!";

            if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
                return;

            toolStripStatusLabel1.Text = "DeCrypting file...";
            this.Cursor = Cursors.WaitCursor;
            Application.DoEvents();

            timer execTime = new timer();

            vernash v = new vernash();
            byte[] x = v.vernashDeCrypt(text, txtPassword.Text, true, saveFileDialog.FileName);

            this.Cursor = Cursors.Default;

            if (x == null)
            {
                txtOutput.Text = "ERROR: Unable to DeCrypt Text!";
                toolStripStatusLabel1.Text = "Ready";
                return;
            }

            string txtStrip = "Text DeCrypted in " + execTime.getTimeMS().ToString("#0.00") + " seconds";

            toolStripStatusLabel1.Text = txtStrip;
        }

        private void clearTextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button10_Click(sender, e);
        }

        private void clearOutputToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button7_Click(sender, e);
        }

        private void saveOutputToFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button6_Click(sender, e);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void copyOutputToTextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button4_Click(sender, e);
        }

        private void encryptWithVernashToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button2_Click(sender, e);
        }

        private void decryptToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button3_Click(sender, e);
        }

        private void shuffleTextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button11_Click(sender, e);
        }

        private void unShuffleTextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button12_Click(sender, e);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            // Encrypt with TripleDES
            byte[] keyArray;
            byte[] toEncryptArray;

            txtOutput.Text = string.Empty;

            if (txt3DESpass.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txt3DESpass.Focus();
                return;
            }

            if (txt3DEStext.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Text");
                txt3DEStext.Focus();
                return;
            }

            this.Cursor = Cursors.WaitCursor;
            toolStripStatusLabel1.Text = "EnCrypting...";
            Application.DoEvents();

            timer execTime = new timer();

            try
            {
                toEncryptArray = UTF8Encoding.UTF8.GetBytes(txt3DEStext.Text);

                MD5CryptoServiceProvider hashmd5 = new MD5CryptoServiceProvider();
                keyArray = hashmd5.ComputeHash(UTF8Encoding.UTF8.GetBytes(txt3DESpass.Text));

                TripleDESCryptoServiceProvider tdes = new TripleDESCryptoServiceProvider();
                tdes.Key = keyArray;
                tdes.Mode = CipherMode.ECB;
                tdes.Padding = PaddingMode.PKCS7;

                ICryptoTransform cTransform = tdes.CreateEncryptor();
                byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

                txtOutput.Text = Convert.ToBase64String(resultArray, 0, resultArray.Length);
            }
            catch
            {
                txtOutput.Text = "ERROR: Unable to EnCrypt this text using TripleDES!";
            }

            this.Cursor = Cursors.Default;

            toolStripStatusLabel1.Text = "Text EnCrypted in " + execTime.getTimeMS().ToString("#0.00") + " seconds";
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
                txt3DESpass.PasswordChar = '*';
            else
                txt3DESpass.PasswordChar = (char)0;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            // Decrypt with TripleDES
            byte[] keyArray;
            byte[] toEncryptArray;

            txtOutput.Text = string.Empty;

            if (txt3DESpass.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Password");
                txt3DESpass.Focus();
                return;
            }

            if (txt3DEStext.Text.Length == 0)
            {
                MessageBox.Show("Please Enter a Text");
                txt3DEStext.Focus();
                return;
            }

            this.Cursor = Cursors.WaitCursor;
            toolStripStatusLabel1.Text = "DeCrypting...";
            Application.DoEvents();

            timer execTime = new timer();

            try
            {
                toEncryptArray = Convert.FromBase64String(txt3DEStext.Text);

                MD5CryptoServiceProvider hashmd5 = new MD5CryptoServiceProvider();
                keyArray = hashmd5.ComputeHash(UTF8Encoding.UTF8.GetBytes(txt3DESpass.Text));

                TripleDESCryptoServiceProvider tdes = new TripleDESCryptoServiceProvider();
                tdes.Key = keyArray;
                tdes.Mode = CipherMode.ECB;
                tdes.Padding = PaddingMode.PKCS7;

                ICryptoTransform cTransform = tdes.CreateDecryptor();
                byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

                txtOutput.Text = UTF8Encoding.UTF8.GetString(resultArray);
            }
            catch
            {
                txtOutput.Text = "ERROR: Unable to DeCrypt this text using TripleDES!";
            }

            this.Cursor = Cursors.Default;

            toolStripStatusLabel1.Text = "Text DeCrypted in " + execTime.getTimeMS().ToString("#0.00") + " seconds";

        }

        private void txtText_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((System.Windows.Forms.Control.ModifierKeys == Keys.Control) && (e.KeyChar == 1))
                ((TextBox)sender).SelectAll();
            Application.DoEvents();
        }

        private void txtTextHash_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((System.Windows.Forms.Control.ModifierKeys == Keys.Control) && (e.KeyChar == 1))
                ((TextBox)sender).SelectAll();
            Application.DoEvents();
        }

        private void txt3DEStext_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((System.Windows.Forms.Control.ModifierKeys == Keys.Control) && (e.KeyChar == 1))
                ((TextBox)sender).SelectAll();
            Application.DoEvents();
        }

    }
}