#!/bin/bash

echo "Testing minishell signal handling..."
echo "This script will test if Ctrl+C properly sets exit status to 130"
echo ""
echo "Instructions:"
echo "1. Run: ./minishell"
echo "2. Type: echo hello"
echo "3. Press Ctrl+C while the command is running"
echo "4. Type: echo \$?"
echo "5. Expected result: 130"
echo ""
echo "Try this with both built-in commands (echo) and external commands (/bin/sleep 5)"
