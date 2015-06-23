for set = [4,10]
    figure(100+set);
    for dim = 1:3
        window = 10;
        nrg = [];
        for w = 1:(length(wdata)-window)
            nrg(dim,end+1) = sum(wdata(w:w+window-1,set+dim-1).^2);
        end
        subplot(3,1,dim);
        plot(1:length(nrg),nrg);
    end
end