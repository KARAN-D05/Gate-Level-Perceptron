% MCP Neuron - AND and OR Gate Emulation
% Two unweighted binary inputs, sum compared against threshold theta
% A simplistic 2-Input model of MCP Neuron, the detector_v1.0 is essentially a multi-input MCP Neuron with other modules like XNOR-Equivalence grid, Population counter etc attached to it.
% https://octave-online.net -> Use to compile the MATLAB code and emulate AND and OR logic 

function output = mcp_neuron(x1, x2, theta)
    % Sum the unweighted inputs
    S = x1 + x2;
    % Fire if sum >= threshold
    if S >= theta
        output = 1;
    else
        output = 0;
    end
end

% ---- Test all input combinations ----
inputs = [0 0; 0 1; 1 0; 1 1];

fprintf('=== MCP Neuron: AND Gate (theta = 2) ===\n');
fprintf('x1  x2  |  Output\n');
fprintf('------------------\n');
for i = 1:4
    out = mcp_neuron(inputs(i,1), inputs(i,2), 2);
    fprintf(' %d   %d  |    %d\n', inputs(i,1), inputs(i,2), out);
end

fprintf('\n=== MCP Neuron: OR Gate (theta = 1) ===\n');
fprintf('x1  x2  |  Output\n');
fprintf('------------------\n');
for i = 1:4
    out = mcp_neuron(inputs(i,1), inputs(i,2), 1);
    fprintf(' %d   %d  |    %d\n', inputs(i,1), inputs(i,2), out);
end
