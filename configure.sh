echo "running make..."
make > /dev/null
echo -n "done"
echo ""

echo -n "modifying .bashrc ..."
echo "\n# Function for wrapping the output of global_pop_dir so we can cd\nfunction gpopdir() {\n\tcd \"\$(global_pop_dir)\"\n}" >> ~/.bashrc
echo -n "done"
echo ""

echo -n "copying executables to /usr/local/bin ..."
cp gpushdir /usr/local/bin
cp global_pop_dir /usr/local/bin
echo -n "done"
echo ""

echo "running make clean..."
make clean > /dev/null
echo "done" 
echo "success"

exit