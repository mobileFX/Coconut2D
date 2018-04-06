
// Open a Game Engine or any class with FSM States and run this Macro while the code editor of the Class is active.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function setStateAttrs(S)
{
	S.error			= /(ERROR)/i.test(S.id);
	S.start			= /(VALIDATE)/i.test(S.id) && !S.error;
	S.final			= /(FINALIZE)/i.test(S.id) && !S.error;
	S.wallet		= /(NETWORK|START)/i.test(S.id);
	S.sandbox		= /SANDBOX/i.test(S.id);
	S.replay		= /RETRIEVE_TICKET/i.test(S.id);
	S.audit			= /PENDING|ALERT/i.test(S.id);
	S.crash			= /RECOVERY/i.test(S.id);
	S.actions		= /ACTIONS|ACTION/i.test(S.id);
	S.ui			= /DISPLAY/i.test(S.id);
	S.rng			= (S.name == '"RNGX"');
	S.weight		= !S.weight && S.error ? 10 : 1000;
	S.dbaccess		= S.body.indexOf(".GetConnection") != -1;
	S.mtdbaccess	= S.body.indexOf(".GetConnection(true)") != -1;
	S.reenter		= S.body.indexOf(S.id) != -1;
	S.lambda		= [];

    var arr, rxLambda = /\[[^\]]*?FUNCTION_NAME[^\]]*?\]\([^\)]*\)[\w\W]*?\{([\w\W]*?)\}\);/mg;
    while ((arr = rxLambda.exec(S.body)) !== null)
    {
        S.lambda.push(arr[1]);
    }

    if (S.start) S.name = '"' + S.vertical + "\\n" + UCapitalize(S.method) + "\\nRequest" + '"';
    if (S.final) S.name = '"' + S.vertical + "\\n" + UCapitalize(S.method) + "\\nResponse" + '"';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function spc(s, c)
{
    if (s.length < c)
        s = s + (new Array(c - s.length)).join(" ");
    return s;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function trim(s)
{
	return (s+"").replace(/^\s+|\s+$/gm,'');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function getFSMStates(code)
{
    var states = {};

    var rxStates = /public state (STATE_\w+)(?:\s+\/\/(GV_\w*\([^)]+\)))*[\w\W]*?\{([\w\W]*?)\};/mg;
    var rxNextState = /setNextState\(([^)]+)\)/mg;
    var rxGvAttrs = /(GV_\w+)\(([^)]+)\)/img;

    while ((arr = rxStates.exec(code)) !== null)
    {
        var stateName = arr[1];

        // Prepare a new STATE
        var STATE = {};
        STATE.id = stateName;
        STATE.name = fixStateName(stateName);
        STATE.method = stateName.split("_")[0];
        STATE.vertical = stateName.split("_")[2];
        STATE.list = {};
        STATE.attrs = [];
        STATE.weight = 0;
        STATE.body = arr[3];

        // Get state body
        var body = arr[0];

        // Get GraphViz attrs
        var attrs = arr[2];

        // Parse GraphViz attrs in code
        while ((arr = rxGvAttrs.exec(attrs)) !== null)
        {
            var name = arr[1];
            var value = arr[2];
            var attr = { "name": name, "value": value };
            if (name == "GV_WEIGHT") STATE.weight = parseInt(value);
            STATE.attrs.push(attr);
        }

        // Simple parse for next states
        while ((arr = rxNextState.exec(body)) !== null)
        {
            var nextState = trim(arr[1]);
           	STATE.list[nextState] = true;
        }

        // Set State attributes from name
        setStateAttrs(STATE);

        // Save state
        states[stateName] = STATE;
    }

    return states;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function fixStateName(name)
{
    name = UCapitalize(name);
    name = name.replace(/iwg /img, "").replace(/slot /img, "");
    name = name.split(" ");
    name = name.slice(1, name.length);
    name = '"' + name.join("\\n") + '"';
    return name;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function UCapitalize(name)
{
    var a = name.split("_");
    for(var i=0; i<a.length; i++)
    {
        var t = a[i];
        t = t.substr(0, 1).toUpperCase() + t.substr(1).toLowerCase();
        a[i] = t;
    }
    return a.join(" ");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function genGraphViz(STATES, title, method)
{
    var HEADER = "";
    HEADER += 'digraph finite_state_machine\n{                                                                                      \n';
    HEADER += '	pad = 0.1;                                                                                                          \n';
    HEADER += '	bgcolor="transparent";                                                                                              \n';
    HEADER += '	rankdir=LR;                                                                                                         \n';
    HEADER += '	ranksep="1.2";                                                                                                      \n';
    HEADER += '                                                                                                                     \n';
    HEADER += '	graph [label="' + title + '" labelloc=t fontname="Arial Black" fontsize=24];                                       \n';
    HEADER += '	edge [concentrate=false penwidth="2" fontname="Verdana" fontsize="12"];                                             \n';
    HEADER += '	node [shape="circle" fixedsize="true" height="1.3" fontname="Verdana" fontsize="12" fontcolor="#000000"];           \n';

    var FOOTER = "";

    var NORMAL_ATTRS    = ' [weight=$(WEIGHT) label="$(LABEL)" taillabel="$(TAIL)" color="#404040"];';
    var ERROR_ATTRS     = ' [label="Error" fontname=Verdana fontsize=9 fontcolor="#ff0000" color="#ff0000"];';
    var RETRY_ATTRS     = ' [weight=$(WEIGHT) label="Retry" fontname=Verdana fontsize=9 fontcolor="#0000ff" color="#0000ff"];';
    var AUDIT_ATTRS     = ' [weight=$(WEIGHT) label="Notify" fontname=Verdana fontsize=9 fontcolor="#0000ff" color="#0000ff"];';

    var STARTING_STATES = [];
    var FINAL_STATES    = [];
    var NORMAL_STATES   = [];
    var RNG_STATES      = [];
    var WALLET_STATES   = [];
    var ERROR_STATES    = [];
    var AUDIT_STATES    = [];
    var CRASH_STATES    = [];
    var ACTIONS_STATES  = [];
    var UI_STATES  		= [];

    var STYLE_STARTING  = '[shape="doublecircle" fillcolor="#F3B7FF" style=filled color="#8C05CC"];';
    var STYLE_FINAL     = '[shape="doublecircle" fillcolor="#F3B7FF" style=filled color="#8C05CC"];';
    var STYLE_NORMAL    = '[fillcolor="#FFFFFF" style=filled color="#000000"];';
    var STYLE_UI    	= '[fillcolor="#C7FFC2" style=filled color="#036D0B"];';
    var STYLE_RNG       = '[fillcolor="#ff0000" style=filled color="#881502" fontcolor="white" fontsize="18" fontname="Verdana Bold" penwidth="3"];';
    var STYLE_WALLET    = '[fillcolor="#B4D3FF" style=filled color="#054ED9" fontcolor="#0433A5" fontsize="14" fontname="Arial Black" penwidth="3"];';
    var STYLE_ERROR     = '[color=red fillcolor="#FFB5B4" style=filled];';
    var STYLE_AUDIT     = '[shape=doublecircle color=red fillcolor="#99043C" fontcolor="white" color="red" style=filled fontname="Verdana Bold"];';
    var STYLE_CRASH     = '[fillcolor="#FE6603" style=filled color="#52025B" fontcolor="white" fontsize="14" fontname="Arial Black" penwidth="4" style="filled,dashed"];';
    var STYLE_ACTIONS   = '[fillcolor="#FFE785" style=filled color="#036D0B"];';

    var LABELS = [];
    var RELATIONS = [];
    var ERROR_RELATIONS = [];
    var RETRIES = [];
    var RANKS = [];

    // Calculate max State ID length (for padding with spaces)
    var name_length = 0;
    for (var state in STATES)
        if (state.length > name_length)
            name_length = state.length;
    name_length += 4;

    // Generate relations
    for (var state in STATES)
    {
        var S = STATES[state];

        if (!S)
        {
            trace("State not found, check for commended line: " + state);
            continue;
        }

        if (method && S.method != method) continue;

        if (S.id == "TICKET_STATE_IWG_RAISE_ALERT" || S.id == "TICKET_STATE_SLOT_RAISE_ALERT") continue;


        /////////////////////////////////////////////////////////
        // Check for Logical Errors and Coding Rules
        /////////////////////////////////////////////////////////

        // Database access must have async retry
        if (S.dbaccess && !S.mtdbaccess && !S.reenter)
        {
            trace("ERROR: Missing state async retry " + S.id);
        }

        // next state in lambdas must be iRGS_SET_NEXT_STATE_FROM_LAMDA
        // Pending Anthousis to eliminate it
        for(var k=0; k<S.lambda.length; k++)
        {
            if(S.lambda[k].indexOf("iRGS_SET_NEXT_STATE(") != -1)
            {
                trace("ERROR: replace iRGS_SET_NEXT_STATE() with iRGS_SET_NEXT_STATE_FROM_LAMDA() in lambda in " + S.id);
            }
        }

        // Create a label for this State
        LABELS.push("\t" + S.id + ' [label=' + S.name + '];');

        // Group states per type
        if (S.start) STARTING_STATES.push(S.id);
        else if (S.final) FINAL_STATES.push(S.id);
        else if (S.audit) AUDIT_STATES.push(S.id);
        else if (S.crash) CRASH_STATES.push(S.id);
        else if (S.wallet && !S.error) WALLET_STATES.push(S.id);
        else if (S.error) ERROR_STATES.push(S.id);
        else if (S.rng) RNG_STATES.push(S.id);
        else if (S.actions) ACTIONS_STATES.push(S.id);
        else if (S.ui) UI_STATES.push(S.id);
        else NORMAL_STATES.push(S.id);

        // Calculate rank
        var has_rank = false;
        var RANK = "{ rank=same " + S.id;
        for (var i = 0; i < S.attrs.length; i++)
        {
            var attr = S.attrs[i];
            if (attr.name == "GV_SAME_RANK")
            {
                RANK += ", " + attr.value;
                has_rank = true;
            }
        }
        if (has_rank)
        {
            RANK += " };";
            RANKS.push("\t" + RANK);
        }

        // Create State relations
        var rel = "";
        for (var next in S.list)
        {
            var N = STATES[next];
            if (!N)
            {
                trace("State not found, check for commended line: " + next);
                continue;
            }

            if (S.audit && !N.audit) continue;

            var weight = S.error ? 1 : N.weight;

            // Create relation
            rel = spc(S.id, name_length) + " -> " + spc(N.id, name_length);

            // Add relation color attributes and caption
            if (S == N)
            {
                rel += RETRY_ATTRS;
                weight = 0;
            }
            else if (N.error)
            {
                rel += ERROR_ATTRS;
                weight = 0;
            }
            else
            {
                rel += NORMAL_ATTRS;
            }

            // Set relation weight
            rel = "\t" + rel;
            rel = rel.replace("$(WEIGHT)", weight);
            rel = rel.replace("$(LABEL)", S.label||"");
            rel = rel.replace("$(TAIL)", S.tail||"");

            // Store relation
            if (S == N)
                RETRIES.push(rel);
            else if (!S.error && N.error)
                ERROR_RELATIONS.push(rel);
            else
                RELATIONS.push(rel);
        }
    }

    // Generate output
    var out = [];

    out.push(HEADER);

    out.push(RANKS.join("\n") + "\n");
    out.push(LABELS.join("\n") + "\n");
    out.push(RELATIONS.join("\n") + "\n");
    out.push(RETRIES.join("\n") + "\n");
    out.push(ERROR_RELATIONS.join("\n") + "\n");

    if (STARTING_STATES.length) out.push("\n\t" + STARTING_STATES.join(", ") + "\n\t" + STYLE_STARTING);
    if (FINAL_STATES.length) out.push("\n\t" + FINAL_STATES.join(", ") + "\n\t" + STYLE_FINAL);
    if (NORMAL_STATES.length) out.push("\n\t" + NORMAL_STATES.join(", ") + "\n\t" + STYLE_NORMAL);
    if (RNG_STATES.length) out.push("\n\t" + RNG_STATES.join(", ") + "\n\t" + STYLE_RNG);
    if (WALLET_STATES.length) out.push("\n\t" + WALLET_STATES.join(", ") + "\n\t" + STYLE_WALLET);
    if (ERROR_STATES.length) out.push("\n\t" + ERROR_STATES.join(", ") + "\n\t" + STYLE_ERROR);
    if (AUDIT_STATES.length) out.push("\n\t" + AUDIT_STATES.join(", ") + "\n\t" + STYLE_AUDIT);
    if (CRASH_STATES.length) out.push("\n\t" + CRASH_STATES.join(", ") + "\n\t" + STYLE_CRASH);
    if (ACTIONS_STATES.length) out.push("\n\t" + ACTIONS_STATES.join(", ") + "\n\t" + STYLE_ACTIONS);
    if (UI_STATES.length) out.push("\n\t" + UI_STATES.join(", ") + "\n\t" + STYLE_UI);


    out.push("\n" + FOOTER);
    out.push('}');

    // Done!
    return out.join("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function main()
{
    var doc = dte.ActiveModule;
    var STATES = getFSMStates(doc.Code);
    var gv = genGraphViz(STATES, doc.NodeName);
    dte.NewModule("$(PROJECT_ROOT)/Application/resources/SlotGameEngine2.gv", gv);
}

// Run!
main();

