CLSID_Process = "3979e8b4-2e86-11db-9c02-0009bf000001";
IID_IProcess = "3b6bc7bd-44c2-11dc-9c02-0009bf000001";

stdin = System.input;
stdout = System.output;
stderr = System.error;
root = System.root;
classStore = ClassStore(root.lookup("class"));
cwd = root;

path = [ "file" ];

function readLine(prompt)
{
    stdout.write(prompt, prompt.length);
    var line = "";
    var c;
    while ((c = stdin.read(1)) != '')
    {
        if (c == '\r' || c == '\n')
        {
            stdout.write("\n", 1);
            return line;
        }
        if (c == '\b' || c == '\x7f')
        {
            if (0 < line.length)
            {
                stdout.write("\b \b", 3);
                line = line.slice(0, -1);
            }
            continue;
        }
        stdout.write(c, 1);
        line += c;
    }
    throw "EOF";
}

elem = /('([^'\\]|\\.)*')|(\"([^"\\]|\\.)*\"|(([^ \\\t]|\\.)+))/g;

function getFile(pathname)
{
    for (var i = 0; i < path.length; ++i)
    {
        var name = path[i] + '/' + pathname;
        try
        {
            return File(root.lookup(name));
        }
        catch (e)
        {
            try
            {
                return File(root.lookup(name + ".js"));
            }
            catch (e)
            {
                return File(root.lookup(name + ".elf"));
            }
        }
    }
}

do {
    var line = readLine("% ");

    var params = line.match(elem);
    if (params.length < 1)
    {
        continue;
    }

    try
    {
        var file = getFile(params[0]);
        var stream = file.stream;
        var x = stream.read(4);
        if (x == "\x7fELF")
        {
            process = classStore.createInstance(CLSID_Process, IID_IProcess);
            process.root = root;
            process.current = cwd;
            process.input = stdin;
            process.output = stdout;
            process.error = stderr;
            process.start(file, params.join(' '));
            process.wait();
        }
        else
        {
            var c = "";
            while ((c = stream.read(255)) != '')
            {
                x += c;
            }
            eval(x);
        }
    }
    catch (e)
    {
        var message = String(e) + '\n';
        stdout.write(message, message.length);
    }
} while (params[0] != 'exit');
