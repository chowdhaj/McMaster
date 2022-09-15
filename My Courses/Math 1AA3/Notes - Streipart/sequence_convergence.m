x = [sqrt(2)];

for i=1:100
   xnew = sqrt(2+x(end));
   x = [x, xnew];
    
    
end


plot(1:length(x),x, '--*', 'LineWidth', 1.2);
ylim([0, 2.3]);

