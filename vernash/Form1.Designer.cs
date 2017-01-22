namespace Vernash
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.button1 = new System.Windows.Forms.Button();
            this.numHashLength = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtTextHash = new System.Windows.Forms.TextBox();
            this.txtText = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.button7 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.button12 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.txtPassword = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.button8 = new System.Windows.Forms.Button();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txt3DEStext = new System.Windows.Forms.TextBox();
            this.txt3DESpass = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.button5 = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveOutputToFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.encryptAFileToAnotherFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.decryptAFileToAnotherFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.clearTextToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.clearOutputToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyOutputToTextToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vernashToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.encryptWithVernashToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.decryptToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.shuffleTextToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.unShuffleTextToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numHashLength)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButton3);
            this.groupBox1.Controls.Add(this.radioButton2);
            this.groupBox1.Controls.Add(this.radioButton1);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.numHashLength);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtTextHash);
            this.groupBox1.Location = new System.Drawing.Point(6, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(525, 199);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Generate an Hash";
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(7, 174);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(84, 17);
            this.radioButton3.TabIndex = 6;
            this.radioButton3.TabStop = true;
            this.radioButton3.Text = "using SHA-1";
            this.radioButton3.UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(7, 151);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(76, 17);
            this.radioButton2.TabIndex = 5;
            this.radioButton2.Text = "using MD5";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(7, 105);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(92, 17);
            this.radioButton1.TabIndex = 1;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "using Vernash";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(405, 171);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(114, 22);
            this.button1.TabIndex = 4;
            this.button1.Text = "Generate";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // numHashLength
            // 
            this.numHashLength.Location = new System.Drawing.Point(105, 125);
            this.numHashLength.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numHashLength.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numHashLength.Name = "numHashLength";
            this.numHashLength.Size = new System.Drawing.Size(125, 20);
            this.numHashLength.TabIndex = 3;
            this.numHashLength.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(31, 127);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Hash Length";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Text";
            // 
            // txtTextHash
            // 
            this.txtTextHash.Location = new System.Drawing.Point(7, 32);
            this.txtTextHash.Multiline = true;
            this.txtTextHash.Name = "txtTextHash";
            this.txtTextHash.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtTextHash.Size = new System.Drawing.Size(512, 67);
            this.txtTextHash.TabIndex = 2;
            this.txtTextHash.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtTextHash_KeyPress);
            // 
            // txtText
            // 
            this.txtText.AllowDrop = true;
            this.txtText.Location = new System.Drawing.Point(12, 66);
            this.txtText.Multiline = true;
            this.txtText.Name = "txtText";
            this.txtText.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtText.Size = new System.Drawing.Size(525, 141);
            this.txtText.TabIndex = 2;
            this.txtText.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtText_KeyPress);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 50);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(28, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Text";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.button7);
            this.groupBox3.Controls.Add(this.button6);
            this.groupBox3.Controls.Add(this.button4);
            this.groupBox3.Controls.Add(this.button10);
            this.groupBox3.Controls.Add(this.txtOutput);
            this.groupBox3.Location = new System.Drawing.Point(12, 272);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(552, 148);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Output";
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(215, 118);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(90, 22);
            this.button7.TabIndex = 3;
            this.button7.Text = "Clear Output";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(311, 118);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(90, 22);
            this.button6.TabIndex = 2;
            this.button6.Text = "Save To File";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(407, 118);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(139, 22);
            this.button4.TabIndex = 1;
            this.button4.Text = "Copy Output To Text";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(119, 118);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(90, 22);
            this.button10.TabIndex = 7;
            this.button10.Text = "Clear Text";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.BackColor = System.Drawing.SystemColors.Window;
            this.txtOutput.Location = new System.Drawing.Point(6, 16);
            this.txtOutput.Multiline = true;
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.ReadOnly = true;
            this.txtOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtOutput.Size = new System.Drawing.Size(540, 96);
            this.txtOutput.TabIndex = 4;
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "All Files|*.*";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.Filter = "Vernash File|*.vsh|All Files|*.*";
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip.Location = new System.Drawing.Point(0, 425);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(572, 22);
            this.statusStrip.TabIndex = 3;
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(39, 17);
            this.toolStripStatusLabel1.Text = "Ready";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.groupBox1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(544, 213);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Hash";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.checkBox1);
            this.tabPage1.Controls.Add(this.button12);
            this.tabPage1.Controls.Add(this.button11);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.txtText);
            this.tabPage1.Controls.Add(this.button3);
            this.tabPage1.Controls.Add(this.button2);
            this.tabPage1.Controls.Add(this.txtPassword);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(544, 213);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Vernash";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.Location = new System.Drawing.Point(68, 5);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(58, 17);
            this.checkBox1.TabIndex = 12;
            this.checkBox1.Text = "hidden";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(418, 34);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(114, 22);
            this.button12.TabIndex = 6;
            this.button12.Text = "UnShuffle";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(418, 5);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(114, 22);
            this.button11.TabIndex = 5;
            this.button11.Text = "Shuffle";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(300, 34);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(114, 22);
            this.button3.TabIndex = 4;
            this.button3.Text = "DeCrypt";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(300, 6);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(114, 22);
            this.button2.TabIndex = 3;
            this.button2.Text = "EnCrypt";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // txtPassword
            // 
            this.txtPassword.Location = new System.Drawing.Point(12, 27);
            this.txtPassword.Name = "txtPassword";
            this.txtPassword.PasswordChar = '*';
            this.txtPassword.Size = new System.Drawing.Size(273, 20);
            this.txtPassword.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 8);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Password";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(12, 27);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(552, 239);
            this.tabControl1.TabIndex = 4;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.button8);
            this.tabPage3.Controls.Add(this.checkBox2);
            this.tabPage3.Controls.Add(this.label5);
            this.tabPage3.Controls.Add(this.txt3DEStext);
            this.tabPage3.Controls.Add(this.txt3DESpass);
            this.tabPage3.Controls.Add(this.label6);
            this.tabPage3.Controls.Add(this.button5);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(544, 213);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "TripleDES";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(422, 33);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(114, 22);
            this.button8.TabIndex = 18;
            this.button8.Text = "DeCrypt";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Checked = true;
            this.checkBox2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox2.Location = new System.Drawing.Point(68, 5);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(58, 17);
            this.checkBox2.TabIndex = 17;
            this.checkBox2.Text = "hidden";
            this.checkBox2.UseVisualStyleBackColor = true;
            this.checkBox2.CheckedChanged += new System.EventHandler(this.checkBox2_CheckedChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 50);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(28, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Text";
            // 
            // txt3DEStext
            // 
            this.txt3DEStext.Location = new System.Drawing.Point(12, 66);
            this.txt3DEStext.Multiline = true;
            this.txt3DEStext.Name = "txt3DEStext";
            this.txt3DEStext.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txt3DEStext.Size = new System.Drawing.Size(525, 141);
            this.txt3DEStext.TabIndex = 14;
            this.txt3DEStext.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txt3DEStext_KeyPress);
            // 
            // txt3DESpass
            // 
            this.txt3DESpass.Location = new System.Drawing.Point(12, 27);
            this.txt3DESpass.Name = "txt3DESpass";
            this.txt3DESpass.PasswordChar = '*';
            this.txt3DESpass.Size = new System.Drawing.Size(273, 20);
            this.txt3DESpass.TabIndex = 13;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 8);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 13);
            this.label6.TabIndex = 16;
            this.label6.Text = "Password";
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(422, 5);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(114, 22);
            this.button5.TabIndex = 0;
            this.button5.Text = "EnCrypt";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.vernashToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(572, 24);
            this.menuStrip1.TabIndex = 5;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFileToolStripMenuItem,
            this.saveOutputToFileToolStripMenuItem,
            this.encryptAFileToAnotherFileToolStripMenuItem,
            this.decryptAFileToAnotherFileToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openFileToolStripMenuItem
            // 
            this.openFileToolStripMenuItem.Name = "openFileToolStripMenuItem";
            this.openFileToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F8;
            this.openFileToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.openFileToolStripMenuItem.Text = "Open File";
            this.openFileToolStripMenuItem.Click += new System.EventHandler(this.openFileToolStripMenuItem_Click);
            // 
            // saveOutputToFileToolStripMenuItem
            // 
            this.saveOutputToFileToolStripMenuItem.Name = "saveOutputToFileToolStripMenuItem";
            this.saveOutputToFileToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.saveOutputToFileToolStripMenuItem.Text = "Save Output to File";
            this.saveOutputToFileToolStripMenuItem.Click += new System.EventHandler(this.saveOutputToFileToolStripMenuItem_Click);
            // 
            // encryptAFileToAnotherFileToolStripMenuItem
            // 
            this.encryptAFileToAnotherFileToolStripMenuItem.Name = "encryptAFileToAnotherFileToolStripMenuItem";
            this.encryptAFileToAnotherFileToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.encryptAFileToAnotherFileToolStripMenuItem.Text = "EnCrypt a File";
            this.encryptAFileToAnotherFileToolStripMenuItem.Click += new System.EventHandler(this.encryptAFileToAnotherFileToolStripMenuItem_Click);
            // 
            // decryptAFileToAnotherFileToolStripMenuItem
            // 
            this.decryptAFileToAnotherFileToolStripMenuItem.Name = "decryptAFileToAnotherFileToolStripMenuItem";
            this.decryptAFileToAnotherFileToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.decryptAFileToAnotherFileToolStripMenuItem.Text = "Decrypt a File";
            this.decryptAFileToAnotherFileToolStripMenuItem.Click += new System.EventHandler(this.decryptAFileToAnotherFileToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.clearTextToolStripMenuItem,
            this.clearOutputToolStripMenuItem,
            this.copyOutputToTextToolStripMenuItem});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // clearTextToolStripMenuItem
            // 
            this.clearTextToolStripMenuItem.Name = "clearTextToolStripMenuItem";
            this.clearTextToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
            this.clearTextToolStripMenuItem.Text = "Clear Text";
            this.clearTextToolStripMenuItem.Click += new System.EventHandler(this.clearTextToolStripMenuItem_Click);
            // 
            // clearOutputToolStripMenuItem
            // 
            this.clearOutputToolStripMenuItem.Name = "clearOutputToolStripMenuItem";
            this.clearOutputToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
            this.clearOutputToolStripMenuItem.Text = "Clear Output";
            this.clearOutputToolStripMenuItem.Click += new System.EventHandler(this.clearOutputToolStripMenuItem_Click);
            // 
            // copyOutputToTextToolStripMenuItem
            // 
            this.copyOutputToTextToolStripMenuItem.Name = "copyOutputToTextToolStripMenuItem";
            this.copyOutputToTextToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
            this.copyOutputToTextToolStripMenuItem.Text = "Copy Output to Text";
            this.copyOutputToTextToolStripMenuItem.Click += new System.EventHandler(this.copyOutputToTextToolStripMenuItem_Click);
            // 
            // vernashToolStripMenuItem
            // 
            this.vernashToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.encryptWithVernashToolStripMenuItem,
            this.decryptToolStripMenuItem,
            this.shuffleTextToolStripMenuItem,
            this.unShuffleTextToolStripMenuItem});
            this.vernashToolStripMenuItem.Name = "vernashToolStripMenuItem";
            this.vernashToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.vernashToolStripMenuItem.Text = "Vernash";
            // 
            // encryptWithVernashToolStripMenuItem
            // 
            this.encryptWithVernashToolStripMenuItem.Name = "encryptWithVernashToolStripMenuItem";
            this.encryptWithVernashToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F2;
            this.encryptWithVernashToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
            this.encryptWithVernashToolStripMenuItem.Text = "Encrypt";
            this.encryptWithVernashToolStripMenuItem.Click += new System.EventHandler(this.encryptWithVernashToolStripMenuItem_Click);
            // 
            // decryptToolStripMenuItem
            // 
            this.decryptToolStripMenuItem.Name = "decryptToolStripMenuItem";
            this.decryptToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F3;
            this.decryptToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
            this.decryptToolStripMenuItem.Text = "Decrypt";
            this.decryptToolStripMenuItem.Click += new System.EventHandler(this.decryptToolStripMenuItem_Click);
            // 
            // shuffleTextToolStripMenuItem
            // 
            this.shuffleTextToolStripMenuItem.Name = "shuffleTextToolStripMenuItem";
            this.shuffleTextToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F4;
            this.shuffleTextToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
            this.shuffleTextToolStripMenuItem.Text = "Shuffle Text";
            this.shuffleTextToolStripMenuItem.Click += new System.EventHandler(this.shuffleTextToolStripMenuItem_Click);
            // 
            // unShuffleTextToolStripMenuItem
            // 
            this.unShuffleTextToolStripMenuItem.Name = "unShuffleTextToolStripMenuItem";
            this.unShuffleTextToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F5;
            this.unShuffleTextToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
            this.unShuffleTextToolStripMenuItem.Text = "UnShuffle Text";
            this.unShuffleTextToolStripMenuItem.Click += new System.EventHandler(this.unShuffleTextToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(572, 447);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.groupBox3);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Vernash v0.5";
            this.Shown += new System.EventHandler(this.Form1_Shown);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numHashLength)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtTextHash;
        private System.Windows.Forms.NumericUpDown numHashLength;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox txtText;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox txtPassword;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem encryptAFileToAnotherFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem decryptAFileToAnotherFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem clearTextToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem clearOutputToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveOutputToFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem copyOutputToTextToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vernashToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem encryptWithVernashToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem decryptToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem shuffleTextToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem unShuffleTextToolStripMenuItem;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txt3DEStext;
        private System.Windows.Forms.TextBox txt3DESpass;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button8;
    }
}

